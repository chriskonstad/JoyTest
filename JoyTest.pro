#-------------------------------------------------
#
# Project created by QtCreator 2014-07-04T12:39:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JoyTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qjoystick.cpp \
    qjoystickinterface.cpp

HEADERS  += mainwindow.h \
    qjoystick.h \
    qjoystickinterface.h

FORMS    += mainwindow.ui

unix:!macx{
LIBS += -lSDL
}

win32{
DEFINES += SDL_WIN
LIBS += -L../JoyTest/depends/windows
LIBS += -lSDL
}
