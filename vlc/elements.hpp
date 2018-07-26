#ifndef TEST_HPP
#define TEST_HPP

#include <QMainWindow>
#include <QWidget>


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
};
#endif
