# xminar27/xvitas02

#-------------------------------------------------
#
# Project created by QtCreator 2015-05-07T00:51:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = icp
TEMPLATE = app


SOURCES += main.cpp \
    Game.cpp \
    Player.cpp \
    Stone.cpp \
    Settings.cpp \
    Spawn.cpp \
    Treasure.cpp \
    End.cpp

HEADERS  += \
    Game.h \
    Player.h \
    Stone.h \
    Settings.h \
    Spawn.h \
    Treasure.h \
    End.h

RESOURCES += \
    res.qrc

FORMS += \
    settings.ui \
    end.ui
