#ifndef BATTERY_H
#define BATTERY_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include <QDebug>
#include <QMutex>
#include <QApplication>

#define DEFTIMER 15000

class Battery : public QObject
{
    Q_OBJECT
public:
    explicit Battery(QObject *parent = nullptr);


signals:
    void update(int);
    void batteryOut();

public slots:
    void run();
    void paused();
    void power(int);

private:
    int batteryPercentage;
    bool stopFlag;
    unsigned long timer;
};

#endif // BATTERY_H
