#include "graphics.hh"

#include <QApplication>
#include <QTime>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    qsrand(QTime::currentTime().msec());

    const int width = 1366;
    const int height = 768;
    const int fps = 60;
    const int refresh_rate = 1000 / fps;

    Graphics graphics(nullptr, width, height, refresh_rate);
    graphics.show();

    return app.exec();
}
