#ifndef CLOCK_H
#define CLOCK_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include <QDebug>
#include <QMutex>
#include <QApplication>

/**
 * @brief The Clock class
 * Clock Class inherits from the QObject class
 * Clock runs as a thread and communicates with the control class to send time
 */

class Clock : public QObject
{
    Q_OBJECT
public:
    explicit Clock(QObject *parent = nullptr);

signals:
    void sendTime(int);//sends the updated time to the control

public slots:
    void run();
    void paused();
    void unpaused();
    void reset();
    //void sendFinal(int);
private:
    int time;
    bool stopped;
};

#endif // CLOCK_H
