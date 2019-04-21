#include "graphics.hh"
#include "vector2d.hh"

#include <QApplication>

#include <cstdlib>
#include <ctime>

constexpr int DEFAULT_N = 100;
constexpr int DEFAULT_I = 1000;

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    std::srand(std::time(NULL));

    const int dim = 1000;
    const int n = (argc >= 2) ? std::atoi(argv[1]) : DEFAULT_N;
    const int i = (argc == 3) ? std::atoi(argv[2]) : DEFAULT_I;

    Graphics graphics(nullptr, dim, n, i);
    graphics.show();

    return app.exec();
}
