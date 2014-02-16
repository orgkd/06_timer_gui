#-------------------------------------------------
#
# Project created by QtCreator 2014-02-14T10:32:30
#
#-------------------------------------------------

QT       += core gui
QT       += winextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 06_timer_gui
TEMPLATE = app


SOURCES += main.cpp\
    dialog.cpp \
    mytimer.cpp

HEADERS  += commonimport.h \
    dialog.h \
    mytimer.h

FORMS    += dialog.ui
