#ifndef BATTERY_H
#define BATTERY_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include <QDebug>
#include <QMutex>
#include <QApplication>

#define DEFTIMER 15000
/**
 * @brief The Battery class
 * Battery Class inherits from the QObject class
 * Battery runs as a thread and communicates with the
 * control class to send updated battery status
 */
class Battery : public QObject
{
    Q_OBJECT
public:
    explicit Battery(QObject *parent = nullptr);


signals:
    void update(int);//sends the updated battery status
    void batteryOut();//send the signal that battery is empty

public slots:
    void run();
    void paused();
    void power(int);

private:
    int batteryPercentage;//state of battery
    bool stopFlag;//stops the clock if true
    unsigned long timer;//Battery percentage changes agter tomer time
};

#endif // BATTERY_H
