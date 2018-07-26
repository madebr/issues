#include "greeter.hpp"

Greeter::Greeter(const QString &name, QObject *parent)
    : QObject(parent)
    , mName(name)
{
}

void Greeter::run()
{
    qDebug() << QString("Hello %1!").arg(mName);

    emit finished();
}
