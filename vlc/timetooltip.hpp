#ifndef TIMETOOLTIP_H
#define TIMETOOLTIP_H

#include <QWidget>

class TimeTooltip : public QWidget
{
    Q_OBJECT
public:
    explicit TimeTooltip( QWidget *parent = 0 );
    void setTip( const QPoint& pos);
    virtual void show();

protected:
    void paintEvent( QPaintEvent * ) override;

private:
    void adjustPosition();
    QPoint mTarget;
};

#endif // TIMETOOLTIP_H
