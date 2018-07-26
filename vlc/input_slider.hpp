/*****************************************************************************
 * input_slider.hpp : VolumeSlider and SeekSlider
 ****************************************************************************
 * Copyright (C) 2006-2011 the VideoLAN team
 * $Id: aad65ce4d49878da9f14b958e837e747d1970436 $
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
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifndef VLC_QT_INPUT_SLIDER_HPP_
#define VLC_QT_INPUT_SLIDER_HPP_

//#ifdef HAVE_CONFIG_H
//# include "config.h"
//#endif

#include <QSlider>
#include <QPainter>
#include <QTime>

#define MSTRTIME_MAX_SIZE 22

class QMouseEvent;
class QWheelEvent;
class QHideEvent;
class QTimer;
class SeekPoints;
class QPropertyAnimation;
class QCommonStyle;
class TimeTooltip;
class QSequentialAnimationGroup;

/* Input Slider derived from QSlider */
class SeekSlider : public QSlider
{
    Q_OBJECT
    Q_PROPERTY(qreal handleOpacity READ handleOpacity WRITE setHandleOpacity)
    Q_PROPERTY(qreal loadingProperty READ loading WRITE setLoading)
public:
    SeekSlider( Qt::Orientation q, QWidget *_parent = 0,
                bool _classic = false );
    virtual ~SeekSlider();
    void setChapters( SeekPoints * );

protected:
    void mouseMoveEvent( QMouseEvent *event ) Q_DECL_OVERRIDE;
    void mousePressEvent( QMouseEvent* event ) Q_DECL_OVERRIDE;
    void mouseReleaseEvent( QMouseEvent *event ) Q_DECL_OVERRIDE;
    void wheelEvent( QWheelEvent *event ) Q_DECL_OVERRIDE;
    void enterEvent( QEvent * ) Q_DECL_OVERRIDE;
    void leaveEvent( QEvent * ) Q_DECL_OVERRIDE;
    void hideEvent( QHideEvent * ) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *ev) Q_DECL_OVERRIDE;

    bool eventFilter( QObject *obj, QEvent *event ) Q_DECL_OVERRIDE;

    QSize sizeHint() const Q_DECL_OVERRIDE;

    void processReleasedButton();
    qreal handleOpacity() const;
    qreal loading() const;
    void setHandleOpacity( qreal opacity );
    void setLoading( qreal loading );
    int handleLength();

    float getValuePercentageFromXPos( int );
    int   getValueFromXPos( int );

private:
    //intf_thread_t *p_intf;
    bool isSliding;        /* Whether we are currently sliding by user action */
    bool isJumping;              /* if we requested a jump to another chapter */
    int inputLength;                           /* InputLength that can change */
    char psz_length[MSTRTIME_MAX_SIZE];               /* Used for the ToolTip */
    QTimer *seekLimitTimer;
    TimeTooltip *mTimeTooltip;
    float f_buffering;
    QTime bufferingStart;
    SeekPoints* chapters;
    bool b_classic;
    bool b_seekable;
    int mHandleLength;

    /* Colors & gradients */
    QSize gradientsTargetSize;
    QLinearGradient backgroundGradient;
    QLinearGradient foregroundGradient;
    QLinearGradient handleGradient;
    QColor tickpointForeground;
    QColor shadowDark;
    QColor shadowLight;

    /* Handle's animation */
    qreal mHandleOpacity;
    qreal mLoading;
    QPropertyAnimation *animHandle;
    QSequentialAnimationGroup *animLoading;
    QTimer *hideHandleTimer;
    QTimer *startAnimLoadingTimer;

public slots:
    void setPosition( float, int64_t, int );
    void setSeekable( bool b ) { b_seekable = b ; }
    void updateBuffering( float );
    void hideHandle();

private slots:
    void startSeekTimer();
    void updatePos();
    void inputUpdated( bool );
    void startAnimLoading();

signals:
    void sliderDragged( float );

};
#endif
