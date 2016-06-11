#-------------------------------------------------
#
# Project created by QtCreator 2016-06-05T12:28:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = server
TEMPLATE = app
CONFIG += c++11
LIBS += `pkg-config opencv --libs`

SOURCES += main.cpp\
        mainwindow.cpp \
    images.cpp \
    showip.cpp

HEADERS  += mainwindow.h \
    common.h \
    images.h

FORMS    += mainwindow.ui
