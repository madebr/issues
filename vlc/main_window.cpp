#include "elements.hpp"

#include <QApplication>
#include <QWidget>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Main Window with the slider
    MainWindow mw;
    mw.show();

    // Create another smaller window to steal focus
    QWidget widget;
    widget.resize(5, 5);
    widget.show();

    return app.exec();
}
