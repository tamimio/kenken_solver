#-------------------------------------------------
#
# Project created by QtCreator 2020-10-11T20:22:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KenKen
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    KenKenSolver.cpp

HEADERS  += mainwindow.h \
    KenKenSolver.h

FORMS    += mainwindow.ui
