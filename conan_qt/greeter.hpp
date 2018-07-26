#include <QDebug>
#include <QObject>
#include <QString>

class Greeter : public QObject
{
    Q_OBJECT
public:
    Greeter(const QString &name, QObject *parent = nullptr);
public slots:
    void run();
signals:
    void finished();
private:
    const QString mName;
};
