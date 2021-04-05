#include "control.h"

Control::Control(QObject *parent): QObject(parent)
{
    batteryLevel = 100;
    powerOn = false;
    currDisplay = HOME;
    currIndex = 0;
    menuCollection.push_front("Records");
    menuCollection.push_front("Frequencies");
    menuCollection.push_front("Programs");

    initFrequencies();
    initPrograms();

}

void Control::start(){
    switch (currDisplay) {

        case HOME:
            powerOn = true;
            emit showDisplay("Welcome to simulator for embedded software used in microcurrent biofeedback devices\n\nClick on Select to get started\n              -------");
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
        case RECORDS:
            emit showDisplay("RECORDS");

            break;
    }
}

void Control::buttonPressed(QString& selection, int button)
{
    if(!powerOn) return;

    if(button == DOWN){
        currIndex = (currIndex == 0) ? 0 : (currIndex - 1) ;
    }
    else if(button == SELECT){
        switch (currDisplay){
            case HOME:
                currDisplay = MENU;
                break;
            case MENU:
                if(selection == "Records"){
                    currDisplay = RECORDS;
                }else if(selection == "Frequencies"){
                    currDisplay = FREQ;
                }else if(selection == "Programs"){
                    currDisplay = PROG;
                }
                break;
            case FREQ:
                frequencyCollection.get(currIndex, &selectedTherapy);
                qDebug()<<selectedTherapy->getName();
                currDisplay = POWER;
                break;
        }
        currIndex =0;
    }
    else if(button == UP){
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
    }
    start();
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
    Therapies* therapy = new Program("Neck", 144, 0);
    programCollection.add(therapy);
    therapy = new Program("Back", 178, 0);
    programCollection.add(therapy);
    therapy = new Program("Legs", 134, 0);
    programCollection.add(therapy);
    therapy = new Program("Hands", 198, 0);
    programCollection.add(therapy);
}




