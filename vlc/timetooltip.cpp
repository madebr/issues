#include "timetooltip.hpp"

#include <QDesktopWidget>
#include <QApplication>

#define TIP_HEIGHT 5

TimeTooltip::TimeTooltip( QWidget *parent ) :
    QWidget( parent )
{
    setWindowFlags( Qt::ToolTip );

    resize( 40, 40 );
}

void TimeTooltip::adjustPosition()
{
    auto s = size();

    QPoint position( mTarget.x() - s.width() / 2, mTarget.y() - s.height() + TIP_HEIGHT / 2 );

    // Keep the tooltip on the same screen if possible
    QRect screen = QApplication::desktop()->screenGeometry( mTarget );
    position.setX( qMax( screen.left(), qMin( position.x(),
        screen.left() + screen.width() - s.width() ) ) );
    position.setY( qMax( screen.top(), qMin( position.y(),
        screen.top() + screen.height() - s.height() ) ) );

    move( position );
}

void TimeTooltip::setTip( const QPoint& target)
{
    mTarget = target;
    adjustPosition();
    update();
    raise();
}

void TimeTooltip::show()
{
    setVisible( true );
    raise();
}

void TimeTooltip::paintEvent( QPaintEvent * )
{
}
