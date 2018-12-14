
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nbody
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += src/main.cc src/graphics.cc

HEADERS += src/graphics.hh
