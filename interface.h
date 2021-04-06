#ifndef INTERFACE_H
#define INTERFACE_H

#include "control.h"
#include "constants.h"
#include <QMainWindow>
#include <QDialog>
#include <QDebug>
#include <QtConcurrent>


namespace Ui {
class Interface;
}

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit Interface(QWidget *parent = nullptr);
    ~Interface();

signals:
    void set(int);

private slots:
    void putDisplay(QString);

    void putBattery(int);

    void putClock(int);

    void on_powerButton_clicked();

    void on_selectButton_clicked();

    void on_upButton_clicked();

    void on_downButton_clicked();

    void on_skinOn_clicked();

    void on_skinOn_2_clicked();

private:
    Ui::Interface *ui;
    Control control;
};

#endif // INTERFACE_H
