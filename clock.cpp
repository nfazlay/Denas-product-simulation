#include "clock.h"

Clock::Clock(QObject *parent) : QObject(parent)
{
    time = 0;
    stopped = false;;

}

void Clock::run()
{
    while(true){

        emit sendTime(time);
        if(stopped == true){
            break;
        }
        time++;
        QThread::currentThread()->msleep(1000);
        QApplication::processEvents();
    }

}

void Clock::paused()
{
    qDebug()<<"Clock Paused";
    stopped = true;

}

void Clock::unpaused()
{
    qDebug()<<"Clock Paused";
    stopped = false;

}

void Clock::reset()
{
    //emit sendFinal(time);
    time =0;
    stopped = true;
    emit sendTime(time);
}
