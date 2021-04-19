# FINAL PROJECT

Denas-PCM System Simulator

## Author

Prateek Khurana 101095539
Hamzah Tariq 101066342
Fazlay Rabbi 101129040

## Files

3000-project-Winter2021.pro
3000-project-Winter2021.pro.user
battery.cpp
battery.h
clock.cpp
clock.h
constants.h
control.cc
control.h
frequency.cpp
frequency.h
interface.cpp
interface.h
interface.ui
main.cpp
program.cpp
program.h
therapies.cpp
therapies.h
therapylist.cpp
therapylist.h
README.md

## Running instruction
    open QT Creator
    Navigate to ./3004-project-Winter2021
    open 3000-project-Winter2021.pro
    go to Build->Run

## Useful Informations about the project
    Welcome to the simlator for Devas-PCM System. The simulator is created using QT and C++, 
    and using several QT Frameworks, namely,
        QMainWindow
        QDialog
        QDebug
        QtConcurrent
        QVector
        QtSql
        QFileInfo
        QDateTime
        QObject
    For the project, we are using observer pattern and the worker object pattern within QT.
    The interface, control, battery and timer run as threads and communicate with each other
    though signals and slots.

    We have used QtSql to store records in a sqlLite database along with timestamp

    The logic behind battery decrease with power:
        Changes the battery consumption according to power level after getting signal from control
        For power 0-10, battery is consumed 2 secnds faster
        For every 10 increse in power untill 50, battery is consumed .5 secs
        For every 10 increse the next 50, battery is consumed .25 secs faster

    States:
        OFF
        HOME
        MENU
        PROG
        FREQ
        POWER
        RECORDS
        TREATMENT
        FINISHED



        




