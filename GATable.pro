#-------------------------------------------------
#
# Project created by QtCreator 2015-03-01T20:48:19
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = GATable
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    event.cpp \
    place.cpp \
    task.cpp \
    matrixplaces.cpp \
    funcs.cpp

HEADERS += \
    event.h \
    place.h \
    task.h \
    matrixplaces.h

OTHER_FILES += \
    inputs.txt
