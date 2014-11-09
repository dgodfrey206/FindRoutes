#-------------------------------------------------
#
# Project created by QtCreator 2014-11-07T11:14:18
#
#-------------------------------------------------

QT       += core gui webkit webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    debugwindow.cpp \
    ../src/db/DataReader.cpp \
    ../src/db/RouteData.cpp \
    ../src/db/StopData.cpp \
    ../src/graph/Edge.cpp \
    ../src/graph/Network.cpp \
    ../src/graph/Node.cpp \
    ../src/graph/Route.cpp \
    ../src/jsoncpp/jsoncpp.cpp


HEADERS  += mainwindow.h \
    debugwindow.h \
    ../src/algorithm/SimAnnealingAlg.h \
    ../src/algorithm/Solver.h \
    ../src/db/DataReader.h \
    ../src/db/RouteData.h \
    ../src/db/StopData.h \
    ../src/graph/Edge.h \
    ../src/graph/Network.h \
    ../src/graph/Node.h \
    ../src/graph/Route.h \
    ../src/graph/TransportType.h \
    ../src/jsoncpp/json/json-forwards.h \
    ../src/jsoncpp/json/json.h


FORMS    += mainwindow.ui \
    debugwindow.ui
