#-------------------------------------------------
#
# Project created by QtCreator 2017-02-27T09:09:28
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AppQuestBDD
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialogconnexion.cpp \
    dialogabout.cpp

HEADERS  += mainwindow.h \
    dialogconnexion.h \
    dialogabout.h

FORMS    += mainwindow.ui \
    dialogconnexion.ui \
    dialogabout.ui

TRANSLATIONS += AppQuestBDD_fr_FR.ts\
            AppQuestBDD_es.ts

RESOURCES += \
    mesressources.qrc
