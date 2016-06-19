#-------------------------------------------------
#
# Project created by QtCreator 2016-06-19T08:35:58
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ActivityManager
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    addactivity.cpp

HEADERS  += mainwindow.h \
    database.h \
    addactivity.h

FORMS    += mainwindow.ui \
    addactivity.ui
