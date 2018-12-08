#include <QApplication>

#include "graphics.hh"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    const int height = 800;
    const int width = 600;
    Graphics graphics(nullptr, height, width);
    graphics.show();
    QImage image = QImage(height, width, QImage::Format_MonoLSB);

    return app.exec();
}
