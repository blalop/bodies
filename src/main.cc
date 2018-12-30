#include "graphics.hh"

#include <QApplication>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    const int height = 600;
    const int width = 800;
    const int fps = 60;
    const int refresh_rate = 1000 / fps;
    Graphics graphics(nullptr, height, width, refresh_rate);
    graphics.show();

    return app.exec();
}
