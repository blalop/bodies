
QT += core gui widgets

TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++14
SOURCES += src/bhtree.cc src/body.cc src/graphics.cc src/map.cc src/quadrant.cc src/main.cc 
HEADERS += src/bhtree.hh src/body.hh src/graphics.hh src/map.hh src/quadrant.hh src/vector2d.hh

OBJECTS_DIR = build
MOC_DIR = build/moc
DESTDIR = bin

brute {
    DEFINES += BRUTE
    TARGET = nbody_brute
}

bhtree {
    DEFINES += BHTREE
    TARGET = nbody_bhtree
}

parallel {
    DEFINES += PARALLEL
    TARGET = nbody_parallel
}