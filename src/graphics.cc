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

    for (auto i = 0; i < N; i++) {
        b[i].x = rand() % this->width;
        b[i].y = rand() % this->height;
        b[i].dx = rand() % 2 - 1;
        b[i].dy = rand() % 2 - 1;
    }
}

Graphics::~Graphics() {
    delete this->timer;
}

void Graphics::drawBody(Body &b) {
    this->image.setPixel(b.x, b.y, black);
    if (b.x == this->width-1 || b.y == this->height-1 || b.x == 0 || b.y == 0) {
        b.x = rand() % this->width;
        b.y = rand() % this->height;
        b.dx = rand() % 2 - 1;
        b.dy = rand() % 2 - 1;
    } else {
        b.x = b.x + b.dx;
        b.y = b.y + b.dy;
    }
    this->image.setPixel(b.x, b.y, white);
}

void Graphics::calculate() {
    for (auto i = 0; i < N; i++) {
        this->drawBody(b[i]);
    }
    this->update();
}

void Graphics::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawImage(0, 0, this->image);
}
