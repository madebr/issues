#include "input_slider.hpp"
#include "timetooltip.hpp"

#include <QMouseEvent>

#include <iostream>

SeekSlider::SeekSlider( QWidget *_parent )
          : QSlider( Qt::Horizontal, _parent )
{
    mTimeTooltip = new TimeTooltip( NULL );
    mTimeTooltip->setMouseTracking( true );

    setMouseTracking( true );
}

SeekSlider::~SeekSlider()
{
    delete mTimeTooltip;
}

void SeekSlider::mouseMoveEvent( QMouseEvent *event )
{
    int margin = 24; //handleLength();
    int posX = qMax( rect().left() + margin, qMin( rect().right() - margin, event->x() ) );

    QString chapterLabel;

    QPoint target( event->globalX() - ( event->x() - posX ), QWidget::mapToGlobal( QPoint( 0, 0 ) ).y() );
    mTimeTooltip->setTip( target );
    event->accept();
}

void SeekSlider::enterEvent( QEvent * )
{
    mTimeTooltip->show();
}

void SeekSlider::leaveEvent( QEvent * )
{
    mTimeTooltip->hide();
}

void SeekSlider::hideEvent( QHideEvent * )
{
    mTimeTooltip->hide();
}