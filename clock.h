#ifndef CLOCK_H
#define CLOCK_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include <QDebug>
#include <QMutex>
#include <QApplication>

class Clock : public QObject
{
    Q_OBJECT
public:
    explicit Clock(QObject *parent = nullptr);

signals:
    void sendTime(int);

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
