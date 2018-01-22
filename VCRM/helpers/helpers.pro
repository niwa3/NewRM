TARGET = helper
TEMPLATE = lib
CONFIG += shared c++11 x86_64
QT += network sql xml
QT -= gui
greaterThan(QT_MAJOR_VERSION, 4): QT += qml
DEFINES += TF_DLL
DESTDIR = ../lib
INCLUDEPATH += ../models/ ../models/sqlobjects/
DEPENDPATH  += ../models/ ../models/sqlobjects/
LIBS += -L../lib -lmodel -lcurl
MOC_DIR = .obj/
OBJECTS_DIR = .obj/

include(../appbase.pri)

HEADERS += applicationhelper.h
SOURCES += applicationhelper.cpp
HEADERS += xmlhelper.h
SOURCES += xmlhelper.cpp
HEADERS += curlhelper.h
SOURCES += curlhelper.cpp
