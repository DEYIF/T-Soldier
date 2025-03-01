#-------------------------------------------------
#
# Project created by QtCreator 2022-08-18T10:46:00
#
#-------------------------------------------------

QT       += core gui
QT += phonon

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UnderGround
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        login.cpp \
    setting.cpp \
    game.cpp \
    hero.cpp \
    enemy.cpp \
    choose.cpp \
    pause.cpp \
    dia.cpp \
    dialog.cpp \
    diamop.cpp \
    diaboard.cpp \
    diamarineboard.cpp \
    diavictory.cpp \
    help.cpp

HEADERS += \
        login.h \
    setting.h \
    game.h \
    hero.h \
    enemy.h \
    choose.h \
    pause.h \
    dia.h \
    dialog.h \
    diamop.h \
    diaboard.h \
    diamarineboard.h \
    diavictory.h \
    help.h

FORMS += \
        login.ui \
    setting.ui \
    game.ui \
    choose.ui \
    pause.ui \
    dia.ui \
    dialog.ui \
    diamop.ui \
    diaboard.ui \
    diamarineboard.ui \
    diavictory.ui \
    help.ui

RESOURCES += \
    pic.qrc
