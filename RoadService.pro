#-------------------------------------------------
#
# Project created by QtCreator 2016-03-18T18:49:24
#
#-------------------------------------------------

QT       += core gui widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RoadService
TEMPLATE = app


SOURCES += main.cpp\
        roadservice.cpp \
    listener.cpp \
    gamefile.cpp \
    gamemodel.cpp \
    player.cpp \
    square.cpp \
    utils.cpp \
    levelmanager.cpp

HEADERS  += roadservice.h \
    listener.h \
    gamefile.h \
    player.h \
    square.h \
    gamemodel.h \
    utils.h \
    levelmanager.h

FORMS    += roadservice.ui


CONFIG += c++11
