#-------------------------------------------------
#
# Project created by QtCreator 2014-11-01T12:56:14
#
#-------------------------------------------------

QT  += core gui
QT  += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nutritioncalc
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    loginctl.cpp \
    logindialog.cpp

HEADERS  += mainwindow.h \
    loginctl.h \
    logindialog.h

FORMS    += mainwindow.ui \
    logindialog.ui

OTHER_FILES += \
    main.qml

QTPLUGIN += QSQLMYSQL

RESOURCES += \
    nutrition.qrc


