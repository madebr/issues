#include "greeter.hpp"

#include <QCoreApplication>
#include <QObject>
#include <QString>
#include <QTimer>

int main(int argc, char *argv[]){
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("Application Example");
    QCoreApplication::setApplicationVersion("1.0.0");

    QString name = argc > 0 ? argv[1] : "";
    if (name.isEmpty()) {
        name = "World";
    }

    Greeter* greeter = new Greeter(name, &app);
    QObject::connect(greeter, &Greeter::finished, &app, QCoreApplication::quit);
    QTimer::singleShot(0, greeter, SLOT(run()));

    return app.exec();
}
