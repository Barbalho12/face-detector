QT += core
QT -= gui

TARGET = client
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11
LIBS += `pkg-config opencv --libs`

TEMPLATE = app

HEADERS += \
    libs/common_dht_read.h \
    libs/Beaglebone_Black/bbb_dht_read.h \
    libs/Beaglebone_Black/bbb_mmio.h \
    libs/BlackLib/v3_0/BlackCore.h \
    libs/BlackLib/v3_0/BlackDef.h \
    libs/BlackLib/v3_0/BlackErr.h \
    libs/BlackLib/v3_0/BlackGPIO/BlackGPIO.h

SOURCES += main.cpp \
    connection_socket.cpp \
    libs/common_dht_read.cpp \
    libs/Beaglebone_Black/bbb_dht_read.cpp \
    libs/Beaglebone_Black/bbb_mmio.cpp \
    libs/BlackLib/v3_0/BlackCore.cpp \
    libs/BlackLib/v3_0/BlackGPIO/BlackGPIO.cpp

