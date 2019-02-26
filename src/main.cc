#include "data/vector2d.hh"
#include "graphics.hh"

#include <QApplication>

#include <cstdlib>
#include <ctime>

constexpr int DEFAULT_N = 100;

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    std::srand(std::time(NULL));

    const int width = 1000;
    const int height = 1000;
    const Vector2D<int> dim = Vector2D<int>(width, height);
    const int fps = 60;
    const int refresh_rate = 1000 / fps;
    const int n = (argc == 2) ? std::atoi(argv[1]) : DEFAULT_N;

    Graphics graphics(nullptr, dim, refresh_rate, n);
    graphics.show();

    return app.exec();
}