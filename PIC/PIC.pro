#-------------------------------------------------
#
# Project created by QtCreator 2014-05-15T15:07:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PIC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    codezeile.cpp \
    parser.cpp \
    steuerwerk.cpp \
    alu.cpp \
    speicher.cpp \
    ram.cpp \
    programmspeicher.cpp \
    programmzaehler.cpp \
    wregister.cpp \
    stack.cpp \
    bitoperationen.cpp \
    timersteuerung.cpp \
    laufzeitzaehler.cpp \
    interruptsteuerung.cpp

HEADERS  += mainwindow.h \
    codezeile.h \
    parser.h \
    steuerwerk.h \
    alu.h \
    speicher.h \
    ram.h \
    programmspeicher.h \
    programmzaehler.h \
    wregister.h \
    stack.h \
    bitoperationen.h \
    timersteuerung.h \
    laufzeitzaehler.h \
    interruptsteuerung.h

FORMS    += mainwindow.ui
