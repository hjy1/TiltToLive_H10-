#-------------------------------------------------
#
# Project created by QtCreator 2020-11-25T23:14:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TiltToLive
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    tool.cpp \
    vector.cpp \
    circle.cpp \
    object.cpp \
    redpoint.cpp \
    gameengine.cpp \
    arrow.cpp \
    clickableview.cpp \
    constants.cpp \
    gunbullet.cpp \
    boom.cpp \
    annulusitem.cpp \
    shockwave.cpp \
    swirl.cpp \
    effect.cpp

HEADERS += \
        mainwindow.h \
    tool.h \
    vector.h \
    circle.h \
    object.h \
    constants.h \
    redpoint.h \
    gameengine.h \
    arrow.h \
    clickableview.h \
    gunbullet.h \
    boom.h \
    annulusitem.h \
    shockwave.h \
    swirl.h \
    effect.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc \
    resources.qrc \
    resources.qrc
