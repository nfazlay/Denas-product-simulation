#-------------------------------------------------
#
# Project created by QtCreator 2021-03-18T02:56:28
#
#-------------------------------------------------

QT       += core gui concurrent sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3000-project-Winter2021
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        battery.cpp \
        clock.cpp \
        control.cc \
        frequency.cpp \
        main.cpp \
        interface.cpp \
        program.cpp \
        therapies.cpp \
        therapylist.cpp

HEADERS += \
        battery.h \
        clock.h \
        constants.h \
        control.h \
        frequency.h \
        interface.h \
        program.h \
        therapies.h \
        therapylist.h

FORMS += \
        interface.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
