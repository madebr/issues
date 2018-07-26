#ifndef VLC_QT_INPUT_SLIDER_HPP_
#define VLC_QT_INPUT_SLIDER_HPP_

#include <QSlider>

class TimeTooltip;

class SeekSlider : public QSlider
{
    Q_OBJECT
public:
    SeekSlider( QWidget *_parent = 0 );
    virtual ~SeekSlider();

protected:
    void mouseMoveEvent( QMouseEvent *event ) Q_DECL_OVERRIDE;
    void enterEvent( QEvent * ) Q_DECL_OVERRIDE;
    void leaveEvent( QEvent * ) Q_DECL_OVERRIDE;
    void hideEvent( QHideEvent * ) Q_DECL_OVERRIDE;

private:
    TimeTooltip *mTimeTooltip;

};
#endif
