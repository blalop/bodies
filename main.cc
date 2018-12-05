#include <QApplication>

#include "graphics.hh"

int main(int argc, char **argv) {
    QApplication a(argc, argv);

    const int height = 400;
    const int width = 400;
    graphics w(0, height, width);
    w.show();

    return a.exec();
}
