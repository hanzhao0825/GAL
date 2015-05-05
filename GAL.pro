#-------------------------------------------------
#
# Project created by QtCreator 2015-04-18T15:36:07
#
#-------------------------------------------------

QT       += core gui
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GAL
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    galscene.cpp \
    galtextboard.cpp \
    galstatus.cpp \
    galbgm.cpp

HEADERS  += widget.h \
    galscene.h \
    galtextboard.h \
    galstatus.h \
    galbgm.h

FORMS    += widget.ui

DISTFILES +=

RESOURCES += \
    gal.qrc