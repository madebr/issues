#include "elements.hpp"

#include <QApplication>
#include <QWidget>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mw;
    mw.show();

    QWidget widget;
    widget.resize(5, 5);
    widget.show();

    return app.exec();
}
