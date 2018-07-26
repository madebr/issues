#ifndef TEST_HPP
#define TEST_HPP

#include <QMainWindow>
#include <QTimer>
#include <QWidget>

class QBoxLayout;
class QTimer;
class SeekSlider;



class Content : public QWidget
{
    Q_OBJECT
public:
    explicit Content(QWidget *parent = nullptr);
    QBoxLayout *mLayout;
	SeekSlider *mSeekSlider;
	QTimer *mTimer;
	unsigned mCounter;
private slots:
    void timerShot();
};


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

	void mouseMoveEvent(QMouseEvent *event) override;
    Content *mContent;
};
#endif
