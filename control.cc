#include "control.h"

Control::Control(QObject *parent): QObject(parent)
{
    operating = false;
    currDisplay = OFF;
    currIndex = 0;
    tempTime = 0;
    skinOn = false;
    recording = false;
    path = "database/records.sqlite";

    menuCollection.push_front("Records");
    menuCollection.push_front("Frequencies");
    menuCollection.push_front("Programs");

    initFrequencies();
    initPrograms();
    initBattery();
    initClock();


}

void Control::start(){
    switch (currDisplay) {
        case OFF:
            emit showDisplay("");
            break;
        case HOME:
            emit showDisplay("Welcome to simulator for embedded software used in microcurrent biofeedback devices\n\nClick on SELECT to get started\n              -------");
            break;
        case MENU:
            emit showDisplay(menuCollection.at(currIndex));
            break;
        case PROG:
            Therapies* program ;
            programCollection.get(currIndex, &program);
            emit showDisplay(program->getName());
            break;
        case FREQ:
            Therapies* freq ;
            frequencyCollection.get(currIndex, &freq);
            emit showDisplay(freq->getName());
            break;
        case POWER:
            emit showDisplay("POWER: "+ QString::number(currIndex));
            break;
        case TREATMENT:
            if(skinOn){
                emit changePower(selectedTherapy.getPower());
                emit clockUnpaused();
                emit clockStart();
                emit showDisplay("Treatment in porgress...\n\nPress SELECT to end");
            }
            else{
                emit changePower(-1);
                emit clockPaused();
                emit showDisplay("Paused\n\nPress SELECT to end");
            }
            break;
        case FINISHED:
            emit showDisplay("Fnished");
            break;
        case RECORDS:
            emit showDisplay("RECORDS");
            break;
    }
}

void Control::powerOn()
{
    if(!operating){
        currDisplay = HOME;
        operating = true;
        emit batteryPaused();
        emit batteryStart();

    }
    else{
        operating = false;
        currDisplay = OFF;
        currIndex = 0;
        tempTime = 0;

        emit changePower(-1);
        emit batteryPaused();
    }
    emit clockReset();
    start();

}

void Control::buttonPressed(int button)
{
    if(button == SKINON) {
        skinOn = true;
        start();
        return;
    }
    if(button == SKINOFF) {
        skinOn = false;
        start();
        return;
     }

    if(button == RECORD){
        recording = !recording;
        return;
    }

    if(!operating || currDisplay == FINISHED) return;

    if(button == SELECT){
        switch (currDisplay){
            case HOME:
                currDisplay = MENU;
                break;
            case MENU:
                if(currIndex == 0){
                    currDisplay = PROG;
                }else if(currIndex ==1){
                    currDisplay = FREQ;
                }else if(currIndex == 2){
                    currDisplay = RECORDS;
                }
                break;
            case FREQ:
                Therapies* tempFreq;
                frequencyCollection.get(currIndex, &tempFreq);
                selectedTherapy = *tempFreq;
                qDebug()<<selectedTherapy.getName();
                currDisplay = POWER;
                break;
            case PROG:
                Therapies* tempProg;
                programCollection.get(currIndex, &tempProg);
                selectedTherapy = *tempProg;
                qDebug()<<selectedTherapy.getName();
                currDisplay = TREATMENT;
                break;
            case POWER:
                selectedTherapy.setPower(currIndex);
                currDisplay = TREATMENT;
                break;
            case TREATMENT:
                emit changePower(-1);
                emit clockPaused();
                makeRecord();
                currDisplay = FINISHED;
        }
        currIndex =0;
        start();
        return;
    }
    if(currDisplay == TREATMENT){
        return;
    }

    if(button == DOWN){
        currIndex = (currIndex == 0) ? 0 : (currIndex - 1) ;
        start();
        return;
    }

    if(button == UP){
        switch (currDisplay) {
            case MENU:
                if(currIndex < menuCollection.size()-1){
                    currIndex += 1;
                }
                break;
            case FREQ:
                if(currIndex < frequencyCollection.getSize()-1){
                    currIndex += 1;
                }
                break;
            case PROG:
                if(currIndex < programCollection.getSize()-1){
                    currIndex += 1;
                }
                break;
            case POWER:
                if(currIndex < 100){
                    currIndex += 1;
                }
                break;
        }
        start();
        return;
    }

}

void Control::batteryRun(int batteryPer)
{
    emit updateBattery(batteryPer);
}

void Control::clockRun(int time)
{
    tempTime = time;
    emit updateClock(time);
}

void Control::makeRecord()
{
    QSqlDatabase records;
    records = QSqlDatabase::addDatabase("QSQLITE");
    records.setDatabaseName("database/records.sqlite");
    if(!records.open()){
        qDebug()<<"Error opening database";
    }
    if(!(records.tables().contains(QLatin1String("recordtable")))){
        QString query = "CREATE TABLE recordtable ("
                        "TherapyName VARCHAR(20),"
                        "Power integer,"
                        "Frequency integer,"
                        "Time integer);";
        QSqlQuery qqry;

        if(!qqry.exec(query)){
            qDebug()<<"Error creating table";
        }
    }
    QString name = selectedTherapy.getName();
    int power = selectedTherapy.getPower();
    int frequency = selectedTherapy.getFrequency();
    addRecord(name, power, frequency, tempTime);

    records.close();
}

void Control::addRecord(QString name, int power, int frequency, int time)
{
    QSqlQuery qqry;

    qqry.prepare("INSERT INTO recordtable ("
                 "TherapyName,"
                 "Power,"
                 "Frequency,"
                 "Time)"
                 "VALUES (?,?,?,?);");

    qqry.addBindValue(name);
    qqry.addBindValue(power);
    qqry.addBindValue(frequency);
    qqry.addBindValue(time);

    if(!qqry.exec()){
        qDebug()<<"Error adding data";
    }
}

void Control::initBattery()
{
    battery = new Battery();
    battery->moveToThread(&batThread);
    connect(this, SIGNAL(batteryStart()), battery, SLOT(run()));
    connect(this, SIGNAL(batteryPaused()), battery, SLOT(paused()));
    connect(this, SIGNAL(changePower(int)), battery, SLOT(power(int)));
    connect(battery, SIGNAL(update(int)), this, SLOT(batteryRun(int)));
    connect(battery, SIGNAL(batteryOut()), this, SLOT(powerOn()));
    batThread.start();
}

void Control::initClock()
{
    clock = new Clock();
    clock->moveToThread(&cloThread);
    connect(this, SIGNAL(clockStart()), clock, SLOT(run()));
    connect(this, SIGNAL(clockPaused()), clock, SLOT(paused()));
    connect(this, SIGNAL(clockUnpaused()), clock, SLOT(unpaused()));
    connect(this, SIGNAL(clockReset()), clock, SLOT(reset()));
    //connect(this, SIGNAL(sendFinal(int)), battery, SLOT(makeRecord(int)));
    connect(clock, SIGNAL(sendTime(int)), this, SLOT(clockRun(int)));
    cloThread.start();
}

void Control::initFrequencies(){
    Therapies* therapy = new Frequency("144hz", 144, 0);
    frequencyCollection.add(therapy);
    therapy = new Frequency("178hz", 178, 0);
    frequencyCollection.add(therapy);
    therapy = new Frequency("134hz", 134, 0);
    frequencyCollection.add(therapy);
    therapy = new Frequency("198hz", 198, 0);
    frequencyCollection.add(therapy);
}

void Control::initPrograms(){
    Therapies* therapy = new Program("Neck", 144, 45);
    programCollection.add(therapy);
    therapy = new Program("Back", 178, 38);
    programCollection.add(therapy);
    therapy = new Program("Legs", 134, 90);
    programCollection.add(therapy);
    therapy = new Program("Hands", 198, 15);
    programCollection.add(therapy);
}





