#include "graphics.hh"

#include <cstdlib>
#include <ctime>

Graphics::Graphics(QWidget *parent, int height, int width, int refresh_rate) : QWidget(parent) {
    this->width = width;
    this->height = height;
    this->resize(width, height);
    this->image = QImage(width, height, QImage::Format_MonoLSB);
    this->image.fill(Color::black);

    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(calculate()));
    this->timer->start(refresh_rate);

    srand(time(0));
}

Graphics::~Graphics() {
    delete this->timer;
}

void Graphics::calculate() {
    static int i = 10;
    static int j = 10;
    static int deltai = 1;
    static int deltaj = 1;
    this->image.setPixel(i, j, black);
    if (i == this->width-1 || j == this->height-1 || i == 0 || j == 0) {
        i = rand() % this->width-1;
        j = rand() % this->height-1;
        deltai = rand() % 2 - 1;
        deltai = rand() % 2 - 1;
    } else {
        i += deltai;
        j += deltaj;
    }
    this->image.setPixel(i, j, white);
    this->update();
}

void Graphics::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawImage(0, 0, this->image);
}
