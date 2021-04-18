#include "control.h"

/**
 * @brief Control::Control
 * @param parent
 * Control class initializes the collections,
 * and sets variable to apporpriates
 */
Control::Control(QObject *parent): QObject(parent)
{
    operating = false;
    currDisplay = OFF;
    currIndex = 0;
    tempTime = 0;
    skinOn = false;
    recording = false;
    path = "./records.sqlite";

    menuCollection.push_front("Records");
    menuCollection.push_front("Frequencies");
    menuCollection.push_front("Programs");

    initFrequencies();
    initPrograms();
    initBattery();
    initClock();
}

Control::~Control()
{
    delete clock;
    cloThread.exit();
    //cloThread.wait();
    delete battery;
    batThread.exit();
    //batThread.wait();
}

/**
 * @brief Control::start
 * Sends display message to interface according to State
 */
void Control::start(){
    switch (currDisplay) {
        case OFF:
            emit showDisplay("");
            break;
        case HOME:
            emit showDisplay("Welcome to simulator for embedded software used in microcurrent biofeedback devices\n\nClick on SELECT to get started\n              -------");
            break;
        case MENU:
            emit showDisplay(displayWrapper(menuCollection.at(currIndex)));
            break;
        case PROG:
            Therapies* program ;
            programCollection.get(currIndex, &program);
            emit showDisplay(displayWrapper(program->getName()));
            break;
        case FREQ:
            Therapies* freq ;
            frequencyCollection.get(currIndex, &freq);
            emit showDisplay(displayWrapper(freq->getName()));
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
            if(recordsCollection.isEmpty()){//check if any record exixts
                emit showDisplay("Empty records");
            }
            else{
                emit showDisplay(displayWrapper(recordsCollection.at(currIndex)));
            }
            break;
    }
}

/**
 * @brief Control::powerOn
 * When power button is pressed
 * Checks if already operating
 * The stop the simulation
 * Otherwise start the simulation
 */
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
    recordsCollection.clear();
    emit clockReset();
    start();
}
/**
 * @brief Control::buttonPressed
 * @param button Button pressed from Interface
 * Gets signal from interface and performs tasks accordingly
 * Calls the Start method to display changes
 */
void Control::buttonPressed(int button)
{
    //Sets the skin on boolean to true and sends to
    //the interface the updated message
    if(button == SKINON) {
        skinOn = true;
        start();
        return;
    }
    //sets the skin on boolean to false and sends to
    //the interface he updated message
    if(button == SKINOFF) {
        skinOn = false;
        start();
        return;
     }

    //Sets recording to true or false
    if(button == RECORD){
        recording = !recording;
        return;
    }
    //if the display is not opearing or the Program has finished
    //Button presses have no significance
    if(!operating || currDisplay == FINISHED) return;

    //if Select button pressed
    //Select button is used to change states
    //Cheks which STATE currently in,
    //Checks selection and moves to next appropriate state
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
                    getRecords();
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

    //If down button pressed, decrease the index by one
    if(button == DOWN){
        currIndex = (currIndex == 0) ? 0 : (currIndex - 1) ;
        start();
        return;
    }

    //if up button pressed, increase the index by one by checking boundaries
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
            case RECORDS:
                if(currIndex < recordsCollection.size()-1){
                    currIndex += 1;
                }
                break;
        }
        start();
        return;
    }

}

/**
 * @brief Control::batteryRun
 * @param batteryPer Battery Percentage
 * Sends signal to interface to update battery status
 */
void Control::batteryRun(int batteryPer)
{
    emit updateBattery(batteryPer);
}

/**
 * @brief Control::clockRun
 * @param time Time (int)
 * Sends signal to interface to update clock
 */
void Control::clockRun(int time)
{
    tempTime = time;
    emit updateClock(time);
}

/**
 * @brief Control::makeRecord
 * Creates a record database and calls the
 * addRecord method to add data to database
 */
void Control::makeRecord()
{
    QSqlDatabase records;
    records = QSqlDatabase::addDatabase("QSQLITE");
    records.setDatabaseName(path);
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
    if(recording){
        QString name = selectedTherapy.getName();
        int power = selectedTherapy.getPower();
        int frequency = selectedTherapy.getFrequency();
        addRecord(name, power, frequency, tempTime);
    }

    records.close();
    return;
}

/**
 * @brief Control::addRecord
 * @param name Name
 * @param power Power
 * @param frequency Frequency
 * @param time Time
 * Adds a record the database
 */
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


/**
 * @brief Control::getRecords
 * Gets records from the database and adds to records collection
 */
void Control::getRecords()
{
    QSqlDatabase records;
    records = QSqlDatabase::addDatabase("QSQLITE");
    records.setDatabaseName(path);
    if(!records.open()){
        qDebug()<<"Error opening database";
    }
    QString data= "";
    QSqlQuery qqry;
    qqry.exec("SELECT * from recordtable");
    while (qqry.next()) {
        QString data= "";
        QString name = qqry.value(0).toString();
        QString power = qqry.value(1).toString();
        QString frequency = qqry.value(2).toString();
        QString time = qqry.value(3).toString();
        data = "Name: " + name +" Power: "+ power + " Frequency: "+ frequency +" Time: "+ time;
        recordsCollection.push_back(data);
    }

    records.close();
    return;
}

/**
 * @brief Control::displayWrapper
 * @param q QString containing string to wrap
 * @return QString wrapped accoridng the State
 * The displayWrapper wraps a string with up and down arrows
 * acoridng to the State and loaction in collection
 * The arrows signify if the user can move up or down
 */
QString Control::displayWrapper(QString q)
{
    QString display= "";
    if(currIndex==0){
        display = "^ \n" + q;
        return display;
    }
    int end =-1;
    switch(currDisplay){
        case MENU:
            end = menuCollection.size()-1;
            break;
        case PROG:
            end = programCollection.getSize()-1;
            break;
        case FREQ:
            end = frequencyCollection.getSize()-1;
            break;
        case RECORDS:
            end = recordsCollection.size()-1;
            break;
    }
    if(currIndex == end){
        display = "\n" + q + "\n" + "v";
        return display;
    }
    display = "^\n" + q + "\n" + "v";
    return display;

}

/**
 * @brief Control::initBattery
 * Initializes the battery thread by connecting the slots and signals
 */
void Control::initBattery()
{
    battery = new Battery();
    battery->moveToThread(&batThread);
    connect(this, SIGNAL(batteryStart()), battery, SLOT(run()));
    connect(this, SIGNAL(batteryPaused()), battery, SLOT(paused()));
    connect(this, SIGNAL(changePower(int)), battery, SLOT(power(int)));
    connect(battery, SIGNAL(update(int)), this, SLOT(batteryRun(int)));
    connect(battery, SIGNAL(batteryOut()), this, SLOT(powerOn()));
    connect(&batThread, &QThread::finished, battery, &QObject::deleteLater);
    batThread.start();
}

/**
 * @brief Control::initClock
 * Initializes the clock stread by connecting the slots and signals
 */
void Control::initClock()
{
    clock = new Clock();
    clock->moveToThread(&cloThread);
    connect(this, SIGNAL(clockStart()), clock, SLOT(run()));
    connect(this, SIGNAL(clockPaused()), clock, SLOT(paused()));
    connect(this, SIGNAL(clockUnpaused()), clock, SLOT(unpaused()));
    connect(this, SIGNAL(clockReset()), clock, SLOT(reset()));
    connect(clock, SIGNAL(sendTime(int)), this, SLOT(clockRun(int)));
    connect(&cloThread, &QThread::finished, clock, &QObject::deleteLater);
    cloThread.start();
}

/**
 * @brief Control::initFrequencies
 * Initializes the frequencies
 */
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

/**
 * @brief Control::initPrograms
 * Initializes the porgrams
 */
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





