#include "data/vector2d.hh"
#include "graphics.hh"

#include <QApplication>
#include <QString>
#include <QTime>

constexpr int DEFAULT_N = 100;

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    qsrand(QTime::currentTime().msec());

    const int width = 1366;
    const int height = 768;
    const Vector2D<int> dim = Vector2D<int>(width, height);
    const int fps = 60;
    const int refresh_rate = 1000 / fps;
    const int n = (argc == 2) ? QString(argv[1]).toInt() : DEFAULT_N;

    Graphics graphics(nullptr, dim, refresh_rate, n);
    graphics.show();

    return app.exec();
}
