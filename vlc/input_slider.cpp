/*****************************************************************************
 * input_slider.cpp : VolumeSlider and SeekSlider
 ****************************************************************************
 * Copyright (C) 2006-2011 the VideoLAN team
 * $Id: 1620bdf30022deaaca7385d87575e8f583c50737 $
 *
 * Authors: Clément Stenac <zorglub@videolan.org>
 *          Jean-Baptiste Kempf <jb@videolan.org>
 *          Ludovic Fauvet <etix@videolan.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

//#ifdef HAVE_CONFIG_H
//# include "config.h"
//#endif

//#include "qt.hpp"

#include "input_slider.hpp"
#include "timetooltip.hpp"
//#include "adapters/seekpoints.hpp"
//#include "input_manager.hpp"
//#include "imagehelper.hpp"

#include <QPaintEvent>
#include <QPainter>
#include <QBitmap>
#include <QStyleOptionSlider>
#include <QLinearGradient>
#include <QTimer>
#include <QRadialGradient>
#include <QLinearGradient>
#include <QSize>
#include <QPalette>
#include <QColor>
#include <QPoint>
#include <QPropertyAnimation>
#include <QApplication>
#include <QDebug>
#include <QScreen>
#include <QSequentialAnimationGroup>

//#include <vlc_aout.h>

namespace {
    int const MIN_SLIDER_VALUE = 0;
    int const MAX_SLIDER_VALUE = 10000;

    int const CHAPTER_SPOT_SIZE = 3;

    int const FADE_DURATION = 300;
    int const FADEOUT_DELAY = 2000;
}

void secstotimestr(char text[MSTRTIME_MAX_SIZE], int t) {
    int ms = t % 1000;
    int s = (t / 1000) % 60;
    int m = (t / 60000) % 60;
    snprintf(text, MSTRTIME_MAX_SIZE, "%d:%d:%d", m, s, ms);
}

#define VLC_UNUSED(S) (void)S

SeekSlider::SeekSlider( Qt::Orientation q, QWidget *_parent, bool _static )
          : QSlider( q, _parent ), b_classic( _static ), animLoading( NULL )
{
    isSliding = false;
    isJumping = false;
    f_buffering = 0.0;
    mHandleOpacity = 1.0;
    mLoading = 0.0;
    chapters = NULL;
    mHandleLength = -1;
    b_seekable = true;

    // prepare some static colors
    QPalette p = palette();
    QColor background = p.color( QPalette::Active, QPalette::Window );
    tickpointForeground = p.color( QPalette::Active, QPalette::WindowText );
    tickpointForeground.setHsv( tickpointForeground.hue(),
            ( background.saturation() + tickpointForeground.saturation() ) / 2,
            ( background.value() + tickpointForeground.value() ) / 2 );

    // set the background color and gradient
    QColor backgroundBase( p.window().color() );
    backgroundGradient.setColorAt( 0.0, backgroundBase.darker( 140 ) );
    backgroundGradient.setColorAt( 1.0, backgroundBase );

    // set the foreground color and gradient
    QColor foregroundBase( 50, 156, 255 );
    foregroundGradient.setColorAt( 0.0,  foregroundBase );
    foregroundGradient.setColorAt( 1.0,  foregroundBase.darker( 140 ) );

    // prepare the handle's gradient
    handleGradient.setColorAt( 0.0, p.window().color().lighter( 120 ) );
    handleGradient.setColorAt( 0.9, p.window().color().darker( 120 ) );

    // prepare the handle's shadow gradient
    QColor shadowBase = p.shadow().color();
    if( shadowBase.lightness() > 100 )
        shadowBase = QColor( 60, 60, 60 ); // Palette's shadow is too bright
    shadowDark = shadowBase.darker( 150 );
    shadowLight = shadowBase.lighter( 180 );
    shadowLight.setAlpha( 50 );

    /* Timer used to fire intermediate updatePos() when sliding */
    seekLimitTimer = new QTimer( this );
    seekLimitTimer->setSingleShot( true );

    /* Tooltip bubble */
    mTimeTooltip = new TimeTooltip( NULL );
    mTimeTooltip->setMouseTracking( true );

    /* Properties */
    setRange( MIN_SLIDER_VALUE, MAX_SLIDER_VALUE );
    setSingleStep( 2 );
    setPageStep( 10 );
    setMouseTracking( true );
    setTracking( true );
    setFocusPolicy( Qt::NoFocus );

    /* Use the new/classic style */
    setMinimumHeight( 18 );

    /* Init to 0 */
    setPosition( -1.0, 0, 0 );
    secstotimestr( psz_length, 0 );

    animHandle = new QPropertyAnimation( this, "handleOpacity", this );
    animHandle->setDuration( FADE_DURATION );
    animHandle->setStartValue( 0.0 );
    animHandle->setEndValue( 1.0 );

    QPropertyAnimation *animLoadingIn = new QPropertyAnimation( this, "loadingProperty", this );
    animLoadingIn->setDuration( 2000 );
    animLoadingIn->setStartValue( 0.0 );
    animLoadingIn->setEndValue( 1.0 );
    animLoadingIn->setEasingCurve( QEasingCurve::OutBounce );
    QPropertyAnimation *animLoadingOut = new QPropertyAnimation( this, "loadingProperty", this );
    animLoadingOut->setDuration( 2000 );
    animLoadingOut->setStartValue( 1.0 );
    animLoadingOut->setEndValue( 0.0 );
    animLoadingOut->setEasingCurve( QEasingCurve::OutBounce );

    animLoading = new QSequentialAnimationGroup( this );
    animLoading->addAnimation( animLoadingIn );
    animLoading->addAnimation( animLoadingOut );
    animLoading->setLoopCount( -1 );

    hideHandleTimer = new QTimer( this );
    hideHandleTimer->setSingleShot( true );
    hideHandleTimer->setInterval( FADEOUT_DELAY );

    startAnimLoadingTimer = new QTimer( this );
    startAnimLoadingTimer->setSingleShot( true );
    startAnimLoadingTimer->setInterval( 500 );

    //CONNECT( MainInputManager::getInstance(), inputChanged( bool ), this , inputUpdated( bool ) );
    QObject::connect(this, &SeekSlider::sliderMoved, this, &SeekSlider::startSeekTimer);
    //QObject::connect(this, &SeekSLider::sliderMoved( int ), this, startSeekTimer() );
    QObject::connect(seekLimitTimer, &QTimer::timeout, this, &SeekSlider::updatePos );
    //CONNECT( seekLimitTimer, timeout(), this, updatePos() );
    QObject::connect( hideHandleTimer, &QTimer::timeout, this, &SeekSlider::hideHandle );
    //CONNECT( hideHandleTimer, timeout(), this, hideHandle() );
    QObject::connect( startAnimLoadingTimer, &QTimer::timeout, this, &SeekSlider::startAnimLoading );
    //CONNECT( startAnimLoadingTimer, timeout(), this, startAnimLoading() );
    mTimeTooltip->installEventFilter( this );
}

SeekSlider::~SeekSlider()
{
    delete mTimeTooltip;
}

/***
 * \brief Sets the chapters seekpoints adapter
 *
 * \params SeekPoints initilized with current intf thread
***/
void SeekSlider::setChapters( SeekPoints *chapters_ )
{
    //delete chapters;
    chapters = chapters_;
    //chapters->setParent( this );
}

/***
 * \brief Main public method, superseeding setValue. Disabling the slider when neeeded
 *
 * \param pos Position, between 0 and 1. -1 disables the slider
 * \param time Elapsed time. Unused
 * \param legnth Duration time.
 ***/
void SeekSlider::setPosition( float pos, int64_t time, int length )
{
    VLC_UNUSED(time);
    if( pos == -1.0  || ! b_seekable )
    {
        setEnabled( false );
        mTimeTooltip->hide();
        isSliding = false;
        setValue( 0 );
        return;
    }
    else
        setEnabled( true );

    if( !isSliding )
    {
        setValue( pos * static_cast<float>( maximum() ) );
        if ( animLoading != NULL && pos >= 0.0f && animLoading->state() != QAbstractAnimation::Stopped )
        {
            animLoading->stop();
            mLoading = 0.0f;
        }

    }

    inputLength = length;
}

void SeekSlider::startSeekTimer()
{
    /* Only fire one update, when sliding, every 150ms */
    if( isSliding && !seekLimitTimer->isActive() )
        seekLimitTimer->start( 150 );
}

void SeekSlider::updatePos()
{
    float f_pos = value() / static_cast<float>( maximum() );
    emit sliderDragged( f_pos ); /* Send new position to VLC's core */
}

void SeekSlider::updateBuffering( float f_buffering_ )
{
    if ( f_buffering_ < f_buffering )
        bufferingStart = QTime::currentTime();
    f_buffering = f_buffering_;
    if ( f_buffering > 0.0 || isEnabled() ) {
        animLoading->stop();
        startAnimLoadingTimer->stop();
        mLoading = 0.0;
    }
    repaint();
}

void SeekSlider::inputUpdated( bool b_has_input )
{
    if ( b_has_input == false ) {
        animLoading->stop();
        startAnimLoadingTimer->stop();
        mLoading = 0.0;
        repaint();
    }
    else if ( f_buffering == 0.0 && !isEnabled() )
        startAnimLoadingTimer->start();
}

void SeekSlider::processReleasedButton()
{
    if ( !isSliding && !isJumping ) return;
    isSliding = false;
    bool b_seekPending = seekLimitTimer->isActive();
    seekLimitTimer->stop(); /* We're not sliding anymore: only last seek on release */
    if ( isJumping )
    {
        isJumping = false;
        return;
    }
    if( b_seekPending && isEnabled() )
        updatePos();
}

void SeekSlider::mouseReleaseEvent( QMouseEvent *event )
{
    if ( event->button() != Qt::LeftButton && event->button() != Qt::MidButton )
    {
        QSlider::mouseReleaseEvent( event );
        return;
    }
    event->accept();
    processReleasedButton();
}

void SeekSlider::mousePressEvent( QMouseEvent* event )
{
    /* Right-click */
    if ( !isEnabled() ||
         ( event->button() != Qt::LeftButton && event->button() != Qt::MidButton )
       )
    {
        QSlider::mousePressEvent( event );
        return;
    }

#if 0
    isJumping = false;
    /* handle chapter clicks */
    int i_width = size().width();
    if ( chapters && inputLength && i_width)
    {
        if ( orientation() == Qt::Horizontal ) /* TODO: vertical */
        {
             /* only on chapters zone */
            if ( event->y() < CHAPTER_SPOT_SIZE ||
                 event->y() > ( size().height() - CHAPTER_SPOT_SIZE ) )
            {
                QList<SeekPoint> points = chapters->getPoints();
                int i_selected = -1;
                bool b_startsnonzero = false; /* as we always starts at 1 */
                if ( points.count() > 0 ) /* do we need an extra offset ? */
                    b_startsnonzero = ( points.at(0).time > 0 );
                int i_min_diff = i_width + 1;
                for( int i = 0 ; i < points.count() ; i++ )
                {
                    int x = points.at(i).time / (double)CLOCK_FREQ / inputLength * i_width;
                    int diff_x = abs( x - event->x() );
                    if ( diff_x < i_min_diff )
                    {
                        i_min_diff = diff_x;
                        i_selected = i + ( ( b_startsnonzero )? 1 : 0 );
                    } else break;
                }
                if ( i_selected && i_min_diff < 4 ) // max 4px around mark
                {
                    chapters->jumpTo( i_selected );
                    event->accept();
                    isJumping = true;
                    return;
                }
            }
        }
    }
    #endif

    isSliding = true ;

    setValue( getValueFromXPos( event->x() ) );
    emit sliderMoved( value() );
    event->accept();
}

void SeekSlider::mouseMoveEvent( QMouseEvent *event )
{
    if ( ! ( event->buttons() & ( Qt::LeftButton | Qt::MidButton ) ) )
    {
        /* Handle button release when mouserelease has been hijacked by popup */
        processReleasedButton();
    }

    if ( !isEnabled() ) return event->accept();

    if( isSliding )
    {
        setValue( getValueFromXPos( event->x() ) );
        emit sliderMoved( value() );
    }

    /* Tooltip */
    if ( inputLength > 0 )
    {
        int margin = handleLength();
        int posX = qMax( rect().left() + margin, qMin( rect().right() - margin, event->x() ) );

        QString chapterLabel;
#if 0
        if ( orientation() == Qt::Horizontal ) /* TODO: vertical */
        {
            QList<SeekPoint> points = chapters->getPoints();
            int i_selected = -1;
            for( int i = 0 ; i < points.count() ; i++ )
            {
                int x = margin + points.at(i).time / (double)CLOCK_FREQ / inputLength * (size().width() - 2*margin);
                if ( event->x() >= x )
                    i_selected = i;
            }
            if ( i_selected >= 0 && i_selected < points.size() )
            {
                chapterLabel = points.at( i_selected ).name;
            }
        }
#endif

        QPoint target( event->globalX() - ( event->x() - posX ),
                QWidget::mapToGlobal( QPoint( 0, 0 ) ).y() );
        if( ( size().width() > handleLength() ) ) {
            secstotimestr( psz_length, getValuePercentageFromXPos( event->x() ) * inputLength );
            mTimeTooltip->setTip( target, psz_length, chapterLabel );
        }
    }
    event->accept();
}

void SeekSlider::wheelEvent( QWheelEvent *event )
{
    /* Don't do anything if we are for somehow reason sliding */
    if( !isSliding && isEnabled() )
    {
        int64_t i_size = 5;//var_InheritInteger( p_intf->obj.libvlc, "short-jump-size" );
        int i_mode = 2;//var_InheritInteger( p_intf->obj.libvlc, "hotkeys-x-wheel-mode" );
        if ( ( event->delta() < 0 && i_mode != 3 ) || ( event->delta() > 0 && i_mode == 3 ) )
            i_size = - i_size;
        float posOffset = static_cast<float>( i_size ) / static_cast<float>( inputLength );
        setValue( value() + posOffset * maximum() );
        emit sliderDragged( value() / static_cast<float>( maximum() ) );
    }
    event->accept();
}

void SeekSlider::enterEvent( QEvent * )
{
    /* Cancel the fade-out timer */
    hideHandleTimer->stop();
    /* Only start the fade-in if needed */
    if( isEnabled() && animHandle->direction() != QAbstractAnimation::Forward )
    {
        /* If pause is called while not running Qt will complain */
        if( animHandle->state() == QAbstractAnimation::Running )
            animHandle->pause();
        animHandle->setDirection( QAbstractAnimation::Forward );
        animHandle->start();
    }
    /* Don't show the tooltip if the slider is disabled or a menu is open */
    if( isEnabled() && inputLength > 0 && !qApp->activePopupWidget() )
        mTimeTooltip->show();
}

void SeekSlider::leaveEvent( QEvent * )
{
    hideHandleTimer->start();
    /* Hide the tooltip
       - if the mouse leave the slider rect (Note: it can still be
         over the tooltip!)
       - if another window is on the way of the cursor */
    if( !rect().contains( mapFromGlobal( QCursor::pos() ) ) ||
      ( !isActiveWindow() && !mTimeTooltip->isActiveWindow() ) )
    {
        mTimeTooltip->hide();
    }
}

void SeekSlider::paintEvent( QPaintEvent *ev )
{
    QSlider::paintEvent( ev );
}

void SeekSlider::hideEvent( QHideEvent * )
{
    mTimeTooltip->hide();
}

bool SeekSlider::eventFilter( QObject *obj, QEvent *event )
{
    if( obj == mTimeTooltip )
    {
        if( event->type() == QEvent::MouseMove )
        {
            QMouseEvent* mev = static_cast<QMouseEvent*>( event );

            if( rect().contains( mapFromGlobal( mev->globalPos() ) ) )
                return false;
        }

        if( event->type() == QEvent::Leave ||
            event->type() == QEvent::MouseMove )
        {
            mTimeTooltip->hide();
        }

        return false;
    }

    return QSlider::eventFilter( obj, event );
}

QSize SeekSlider::sizeHint() const
{
    if ( b_classic )
        return QSlider::sizeHint();
    return ( orientation() == Qt::Horizontal ) ? QSize( 100, 18 )
                                               : QSize( 18, 100 );
}

qreal SeekSlider::handleOpacity() const
{
    return mHandleOpacity;
}

qreal SeekSlider::loading() const
{
    return mLoading;
}

void SeekSlider::setHandleOpacity(qreal opacity)
{
    mHandleOpacity = opacity;
    /* Request a new paintevent */
    update();
}

void SeekSlider::setLoading(qreal loading)
{
    mLoading = loading;
    /* Request a new paintevent */
    update();
}

inline int SeekSlider::handleLength()
{
    if ( mHandleLength > 0 )
        return mHandleLength;

    /* Ask for the length of the handle to the underlying style */
    QStyleOptionSlider option;
    initStyleOption( &option );
    mHandleLength = style()->pixelMetric( QStyle::PM_SliderLength, &option );
    return mHandleLength;
}

inline int SeekSlider::getValueFromXPos( int posX )
{
    return QStyle::sliderValueFromPosition(
        minimum(), maximum(),
        posX    - handleLength() / 2,
        width() - handleLength(),
        false
    );
}

inline float SeekSlider::getValuePercentageFromXPos( int posX )
{
    return getValueFromXPos( posX ) / static_cast<float>( maximum() );
}

void SeekSlider::hideHandle()
{
    /* If pause is called while not running Qt will complain */
    if( animHandle->state() == QAbstractAnimation::Running )
        animHandle->pause();
    /* Play the animation backward */
    animHandle->setDirection( QAbstractAnimation::Backward );
    animHandle->start();
}

void SeekSlider::startAnimLoading()
{
    animLoading->start();
}
