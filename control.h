#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QVector>
#include <stdio.h>
#include "therapies.h"
#include "constants.h"
#include "frequency.h"
#include "program.h"
#include "therapylist.h"


class Control : public QObject
{
    Q_OBJECT

public:
    explicit Control(QObject *parent = nullptr);
    void start();

signals:
    void showDisplay(QString);

public slots:
    void buttonPressed(int);

private:
    int batteryLevel;
    bool powerOn;
    bool select;
    int currDisplay;
    int currIndex;
    bool skinOn;
    Therapies* selectedTherapy;
    void initFrequencies();
    void initPrograms();
    QVector<QString> menuCollection;
    TherapyList frequencyCollection;
    TherapyList programCollection;
};

#endif // CONTROL_H
