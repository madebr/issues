#include "elements.hpp"

#include "input_slider.hpp"

#include <Qt>
#include <QVBoxLayout>
#include <QTimer>
#include <QMouseEvent>

Content::Content(QWidget *parent)
    : QWidget(parent)
    , mLayout(new QVBoxLayout{})
    , mSeekSlider(new SeekSlider{Qt::Horizontal})
    , mTimer(new QTimer{})
    , mCounter{0}
{
    mSeekSlider->setSeekable(true);
    mSeekSlider->setPosition(0.0f, 5000, 50000);

    mLayout->addStretch();
    mLayout->addWidget(mSeekSlider);

    connect(mTimer, &QTimer::timeout, this, &Content::timerShot);
    mTimer->start(50);

    setLayout(mLayout);
}

namespace {
    const unsigned MAX_COUNTER = 100000;
}

#include <iostream>
void Content::timerShot()
{
    mCounter = (mCounter + 50) % (MAX_COUNTER);
    float frac = mCounter / float(MAX_COUNTER);
    mSeekSlider->setPosition(mCounter / float(MAX_COUNTER), 0, 50000);
}


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, mContent(new Content{this})
{
	setCentralWidget(mContent);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
}
