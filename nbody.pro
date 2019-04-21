
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nbody
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++14

SOURCES += src/bhtree.cc src/body.cc src/graphics.cc src/map.cc src/quadrant.cc src/main.cc 

HEADERS += src/bhtree.hh src/body.hh src/graphics.hh src/map.hh src/quadrant.hh src/vector2d.hh
