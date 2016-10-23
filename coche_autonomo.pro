#-------------------------------------------------
#
# Project created by QtCreator 2016-10-18T12:23:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = coche_autonomo
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    common.cpp \
    screen_t.cpp \
    map_t.cpp \
    coche_autonomo_t.cpp

HEADERS  += mainwindow.h \
    common.hpp \
    screen_t.hpp \
    map_t.h \
    coche_autonomo_t.h

FORMS    += mainwindow.ui

CONFIG += link_pkgconfig

PKGCONFIG += allegro-5 \
        allegro_ttf-5 \
        allegro_font-5 \
        allegro_primitives-5 \
        allegro_dialog-5 \
        allegro_image-5
QMAKE_CXXFLAGS += -Wall -std=c++11
