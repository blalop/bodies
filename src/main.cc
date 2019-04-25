#include "graphics.hh"
#include "map.hh"

#include <QApplication>

#include <cstdlib>
#include <iostream>

constexpr int DEFAULT_I = 1000;

int main(int argc, char **argv) {
    const int iters = (argc == 2) ? std::atoi(argv[1]) : DEFAULT_I;
    Map map;
    std::cin >> map;

    QApplication app(argc, argv);
    Graphics graphics(nullptr, map, iters);
    graphics.show();
    return app.exec();
}
