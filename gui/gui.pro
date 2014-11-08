#-------------------------------------------------
#
# Project created by QtCreator 2014-11-07T11:14:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    debugwindow.cpp \
    ../src/jsoncpp/jsoncpp.cpp \
    ../src/Edge.cpp \
    ../src/Network.cpp \
    ../src/Node.cpp \
    ../src/Route.cpp

HEADERS  += mainwindow.h \
    debugwindow.h \
    ../src/jsoncpp/json/json-forwards.h \
    ../src/jsoncpp/json/json.h \
    ../src/Edge.h \
    ../src/Network.h \
    ../src/Node.h \
    ../src/Route.h \
    ../src/SimAnnealingAlg.h \
    ../src/Solver.h \
    ../src/TransportType.h

FORMS    += mainwindow.ui \
    debugwindow.ui
