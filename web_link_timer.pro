#-------------------------------------------------
#
# Project created by QtCreator 2016-06-28T22:19:44
#
#-------------------------------------------------

QT       -= core
QT       -= gui

TARGET = web_link_timer
CONFIG   += console
CONFIG   -= app_bundle

QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app

HEADERS += char_tools.h \
    flags.h \
    keyboardinputsender.h \
    logger.h \
    timer.h \
    weblinkmanager.h

SOURCES += char_tools.cpp \
    keyboardinputsender.cpp \
    logger.cpp \
    main.cpp \
    timer.cpp \
    weblinkmanager.cpp

