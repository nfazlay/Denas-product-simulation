#include "clock.h"

/**
 * @brief Clock::Clock
 * @param parent
 * Constructor sets time ti zero and stops the clock
 */
Clock::Clock(QObject *parent) : QObject(parent)
{
    time = 0;
    stopped = false;;

}

/**
 * @brief Clock::run
 * The run fucntion is called when when clock is started
 * It goes in a while loop and emits the sendTime signal to the control to
 * after one second. If the stopped is true, the loop breaks
 */
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

/**
 * @brief Clock::paused
 * Gets signal from control to stop the clock
 */
void Clock::paused()
{
    qDebug()<<"Clock Paused";
    stopped = true;

}

/**
 * @brief Clock::paused
 * Gets signal from control to start the clock
 */
void Clock::unpaused()
{
    qDebug()<<"Clock unpaused";
    stopped = false;

}

/**
 * @brief Clock::paused
 * Gets signal from control to reset the clock
 */
void Clock::reset()
{
    //emit sendFinal(time);
    time =0;
    stopped = true;
    emit sendTime(time);
}
