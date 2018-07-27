#include <QApplication>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QMouseEvent>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>

#define TIP_HEIGHT 5

class TimeTooltip : public QWidget
{
public:
    explicit TimeTooltip( QWidget *parent = 0 )
        : QWidget( parent )
    {
        setWindowFlags( Qt::ToolTip );
        resize( 40, 40 );
    }
    void setTip( const QPoint& pos)
    {
        mTarget = pos;
        adjustPosition();
        update();
        raise();
    }
    virtual void show()
    {
        setVisible( true );
        raise();
    }
private:
    void adjustPosition()
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
    QPoint mTarget;
};

class SeekSlider : public QSlider
{
public:
    SeekSlider( QWidget *_parent = 0 )
          : QSlider( Qt::Horizontal, _parent )
    {
        mTimeTooltip = new TimeTooltip( NULL );
        mTimeTooltip->setMouseTracking( true );

        setMouseTracking( true );
    }
    virtual ~SeekSlider()
    {
        delete mTimeTooltip;
    }

protected:
    void mouseMoveEvent( QMouseEvent *event ) Q_DECL_OVERRIDE
    {
        int margin = 24;
        int posX = qMax( rect().left() + margin, qMin( rect().right() - margin, event->x() ) );

        QPoint pos( event->globalX() - ( event->x() - posX ), QWidget::mapToGlobal( QPoint( 0, 0 ) ).y() );
        mTimeTooltip->setTip( pos );
        event->accept();
    }
    void enterEvent( QEvent * ) Q_DECL_OVERRIDE
    {
        mTimeTooltip->show();
    }
    void leaveEvent( QEvent * ) Q_DECL_OVERRIDE
    {
        mTimeTooltip->hide();
    }
private:
    TimeTooltip *mTimeTooltip;
};

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget *parent = nullptr)
	    : QMainWindow(parent)
    {
        auto central = new QWidget;
        auto slider = new SeekSlider{};
        slider->setEnabled(true);
        auto layout = new QVBoxLayout;
        layout->addStretch();
        layout->addWidget(slider);
        central->setLayout(layout);
        setCentralWidget(central);
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mw;
    mw.show();

    return app.exec();
}
