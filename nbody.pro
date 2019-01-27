
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nbody
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++14

SOURCES += src/body.cc src/graphics.cc src/map.cc src/main.cc 

HEADERS += src/body.hh src/graphics.hh src/map.hh src/data/vector2d.hh
