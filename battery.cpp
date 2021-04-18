#include "battery.h"

/**
 * @brief Battery::Battery
 * @param parent
 * Constructor sets the battery to full,
 * sets the flag to true and
 * sets the timer to Default timer
 */
Battery::Battery(QObject *parent) : QObject(parent)
{
    batteryPercentage = 100;
    stopFlag = true;
    timer = DEFTIMER;
}

/**
 * @brief Battery::run
 * The run is stated when the battery receives signal from the control
 * It goes into a while loop and emits the updated pattery percentage to the control
 * The while loop breaks if the stopFlag is set to true
 */

void Battery::run()
{

    while(batteryPercentage != 0){
        if(stopFlag){
            break;
        }
        emit update(batteryPercentage);
        batteryPercentage--;
        QApplication::processEvents();
        QThread::currentThread()->msleep(timer);
    }

    //send the battery out signal if battery percentage is at zero
    if(batteryPercentage == 0){
        emit update(batteryPercentage);
        stopFlag = true;
        emit batteryOut();
    }

}

/**
 * @brief Battery::paused
 * Gets signal to pause the battery
 */
void Battery::paused()
{
    qDebug()<<"Battery: "<<stopFlag;
    stopFlag = !stopFlag;

}

/**
 * @brief Battery::power
 * @param p power
 * Changes the battery consumption according to power level after getting signal from control
 * For power 0-10, battery is consumed 2 secnds faster
 * For every 10 increse in power untill 50, battery is consumed .5 secs
 * For every 10 increse the next 50, battery is consumed .25 secs faster
 */
void Battery::power(int p)
{
    if(p == -1){
        timer = DEFTIMER;
        qDebug()<<"Battery set to Default";
        return;
    }
    unsigned long tempTimer = 0;
    int div = p/10;
    for(int i = 0; i <= div; i++){
        if(i == 0){
            tempTimer += 2000;
        }
        else if (i <= 5){
            tempTimer += 500;
        }
        else if(i <= 10){
            tempTimer += 250;
        }
    }
    qDebug()<<"Battery Consume faster";
    QMutex mutex;
    mutex.lock();
    timer = timer - tempTimer;
    mutex.unlock();
}
