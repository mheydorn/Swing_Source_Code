#-------------------------------------------------
#
# Project created by QtCreator 2015-05-05T16:04:27
#
#-------------------------------------------------

#FIXME: You have to set this manually each time you move the project directory
include(/home/mheydorn/sandbox/Swing_Source_Code/MotorControl/qextserialport/src/qextserialport.pri)
DEFINES += QEXTSERIALPORT_USING_SHARED
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MotorControl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
