#include "graphics.hh"
#include "map.hh"
#include "vector2d.hh"

#include <QApplication>

#include <cstdlib>

constexpr int DEFAULT_I = 1000;

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    const int iters = (argc == 2) ? std::atoi(argv[1]) : DEFAULT_I;

    Map map;
    Graphics graphics(nullptr, map, iters);
    graphics.show();

    return app.exec();
}
