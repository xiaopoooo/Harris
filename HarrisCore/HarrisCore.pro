#-------------------------------------------------
#
# Project created by QtCreator 2015-01-09T10:47:20
#
#-------------------------------------------------

QT       -= gui

TARGET = HarrisCore
TEMPLATE = lib

DESTDIR = ../lib
DLLDESTDIR = ../bin

DEFINES += HARRISCORE_LIBRARY

SOURCES += harriscore.cpp

HEADERS += harriscore.h\
        harriscore_global.h \
    harris.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include(../Config/link2opencv.pri)
