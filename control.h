#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QVector>
#include <stdio.h>
#include <QtConcurrent>
#include "therapies.h"
#include "constants.h"
#include "frequency.h"
#include "program.h"
#include "therapylist.h"
#include "battery.h"
#include "clock.h"


class Control : public QObject
{
    Q_OBJECT

public:
    explicit Control(QObject *parent = nullptr);


signals:
    void showDisplay(QString);

    void batteryStart();
    void updateBattery(int);
    void batteryPaused();
    void changePower(int);

    void clockStart();
    void updateClock(int);
    void clockPaused();
    void clockReset();

public slots:
    void start();
    void powerOn();
    void buttonPressed(int);

    void batteryRun(int);

    void clockRun(int);


private:
    bool operating;
    int currDisplay;
    int currIndex;
    bool skinOn;
    Battery *battery;
    Clock *clock;
    QThread batThread;
    QThread cloThread;
    Therapies selectedTherapy;
    void init();
    void initFrequencies();
    void initPrograms();
    QVector<QString> menuCollection;
    TherapyList frequencyCollection;
    TherapyList programCollection;
};

#endif // CONTROL_H
