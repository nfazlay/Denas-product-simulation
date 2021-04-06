#include "clock.h"

Clock::Clock(QObject *parent) : QObject(parent)
{
    time = 0;
    stopped = true;;

}

void Clock::run()
{
    while(true){
        if(stopped == true){
            break;
        }
        time++;
        sendTime(time);
        QApplication::processEvents();
        QThread::currentThread()->msleep(1000);
    }

}

void Clock::paused()
{
    qDebug()<<"Clock Paused";
    stopped = !stopped;

}

void Clock::reset()
{
    time =0;
    stopped = true;
}
