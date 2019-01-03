
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nbody
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += src/graphics.cc src/body.cc src/main.cc

HEADERS += src/graphics.hh src/body.hh
