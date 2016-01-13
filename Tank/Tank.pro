#-------------------------------------------------
#
# Project created by QtCreator 2016-01-08T21:17:08
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Tank
CONFIG   += console
CONFIG   -= app_bundle
LIBS += `sdl-config --cflags --libs`

TEMPLATE = app


SOURCES += \
    main.c \
    data.c \
    tank.c \
    events.c \
    move.c \
    draw.c \
    bullet.c \
    units.c \
    shot.c

HEADERS += \
    draw.h \
    defs.h \
    tank.h \
    data.h \
    events.h \
    move.h \
    bullet.h \
    units.h \
    shot.h
