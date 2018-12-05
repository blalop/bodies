
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nbody
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cc graphics.cc

HEADERS += graphics.hh
