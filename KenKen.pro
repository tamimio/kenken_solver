#-------------------------------------------------
#
# Project created by QtCreator 2020-10-11T20:22:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -D_GLIBCXX_DEBUG
#CONFIG += c++11

TARGET = KenKen
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    KenKenSolver.cpp

HEADERS  += mainwindow.h \
    KenKenSolver.h

FORMS    += mainwindow.ui
