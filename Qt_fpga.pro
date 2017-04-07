#-------------------------------------------------
#
# Project created by QtCreator 2017-02-21T20:03:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_fpga
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    jiemian1.cpp \
    serial.cpp \
    curste.cpp \
    base_set.cpp \
    sweep.cpp \
    profil.cpp \
    jiemian2.cpp

HEADERS  += mainwindow.h \
    curste.h \
    serial.h \
    base_set.h \
    Profil.h \
    Sweep.h

FORMS    += mainwindow.ui
