#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QVector>
#include <QtSql>
#include <stdio.h>
#include <QFileInfo>
#include <QtConcurrent>
#include <QDateTime>
#include "therapies.h"
#include "constants.h"
#include "frequency.h"
#include "program.h"
#include "therapylist.h"
#include "battery.h"
#include "clock.h"

/**
 * @brief The Control class
 * Control class controls the main flow of the program
 * Control runs as a thread communicates with the interface
 */
class Control : public QObject
{
    Q_OBJECT

public:
    explicit Control(QObject *parent = nullptr);
    ~Control();

signals:
    void showDisplay(QString);//sends a QString to the interface to display

    void batteryStart();//sends signal to start display

    void updateBattery(int);//sends the signal to update the battery

    void batteryPaused();//sends the signal to pause the battery

    void changePower(int);//send the power signal to the battery to change battery consumption

    void clockStart();//sends signal to start the clock

    void updateClock(int);//sends signal to update tje clock

    void clockPaused();//sends signal that clock is paused

    void clockReset();//resets the clock to zero

    void clockUnpaused();//resumes the clock

public slots:
    void start();

    void powerOn();

    void buttonPressed(int);

    void batteryRun(int);

    void clockRun(int);

private:
    bool operating;//true if operating
    int currDisplay;//stores the state
    int currIndex;//stores the index for navigation
    bool skinOn;//set to true if skin-on button pressed
    bool recording;//set to true if recording button pressed
    int tempTime;//stores time of therapy to be used in record

    QString path;
    Battery *battery;
    Clock *clock;
    QThread batThread;
    QThread cloThread;
    Therapies selectedTherapy;

    void init();
    void initFrequencies();
    void initPrograms();
    void initBattery();
    void initClock();
    void makeRecord();
    void addRecord(QString, int, int, int);
    void getRecords();
    QString displayWrapper(QString);

    QVector<QString> menuCollection;
    QVector<QString> recordsCollection;
    TherapyList frequencyCollection;
    TherapyList programCollection;
};

#endif // CONTROL_H
