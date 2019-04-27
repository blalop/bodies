#include "graphics.hh"
#include "map.hh"

#include <QApplication>

#include <cstdlib>
#include <iostream>

constexpr int DEFAULT_I = 1000;
constexpr double DEFAULT_DT = 1;

int main(int argc, char **argv) {
    const int iters = (argc == 2) ? std::atoi(argv[1]) : DEFAULT_I;
    const double deltatime = (argc == 3) ? std::atof(argv[2]) : DEFAULT_DT;

    Map map(deltatime);
    std::cin >> map;

    QApplication app(argc, argv);
    Graphics graphics(nullptr, map, iters);
    graphics.show();
    return app.exec();
}
