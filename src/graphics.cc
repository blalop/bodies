#include "graphics.hh"

#include <QPoint>

Graphics::Graphics(QWidget *parent, int width, int height, int refresh_rate)
    : QWidget(parent), width(width), height(height), timer(new QTimer) {

    this->resize(width, height);

    this->image = QImage(width, height, QImage::Format_MonoLSB);
    this->image.fill(this->Color::black);

    for (auto i = 0; i < N; i++) {
        b[i].place(this->width, this->height);
    }
    timer.reset(new QTimer);
    QObject::connect(this->timer.data(), SIGNAL(timeout()), this, SLOT(step()));
    this->timer->start(refresh_rate);
}

Graphics::~Graphics() {}

void Graphics::step() {
    this->image.fill(this->Color::black);

    for (auto i = 0; i < N; i++) {
        b[i].resetForce();
        for (auto j = 0; j < N; j++) {
            if (i != j) {
                b[i].addForce(b[j]);
            }
        }
    }
    for (auto i = 0; i < N; i++) {

        QPoint p = b[i].move();
        int x = p.x();
        int y = p.y();

        if (x > -1 && x < this->width && y > -1 && y < this->height) {
            this->image.setPixel(x, y, this->Color::white);
        }
    }
    this->update();
}

void Graphics::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawImage(0, 0, this->image);
}
