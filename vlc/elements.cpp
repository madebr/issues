#include "elements.hpp"

#include "input_slider.hpp"

#include <Qt>
#include <QVBoxLayout>
#include <QTimer>
#include <QMouseEvent>

#include <QSlider>


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
    auto slider = new SeekSlider{};
    slider->setEnabled(true);

    auto central = new QWidget;
    auto layout = new QVBoxLayout;
    layout->addStretch();
    layout->addWidget(slider);
    central->setLayout(layout);
	setCentralWidget(central);
}
