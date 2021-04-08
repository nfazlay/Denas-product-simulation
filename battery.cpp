#include "battery.h"

Battery::Battery(QObject *parent) : QObject(parent)
{
    batteryPercentage = 100;
    stopFlag = true;
    timer = DEFTIMER;
}

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

    if(batteryPercentage == 0){
        emit batteryOut();
    }

}

void Battery::paused()
{
    qDebug()<<"Battery Paused";
    stopFlag = !stopFlag;

}

void Battery::power(int p)
{
    if(p == -1){
        timer = DEFTIMER;
        qDebug()<<"Battery set to original";
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

    QMutex mutex;
    mutex.lock();
    qDebug()<<tempTimer;
    timer = timer - tempTimer;
    mutex.unlock();
}
