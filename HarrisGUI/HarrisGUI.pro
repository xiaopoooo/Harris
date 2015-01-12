#-------------------------------------------------
#
# Project created by QtCreator 2015-01-09T15:26:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HarrisGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc

INCLUDEPATH += ../HarrisCore
LIBS    += -L../lib -lHarrisCore
