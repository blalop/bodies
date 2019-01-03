#include "graphics.hh"

Graphics::Graphics(QWidget *parent, int width, int height, int refresh_rate)
    : QWidget(parent) {
    this->width = width;
    this->height = height;
    this->resize(width, height);

    this->image = QImage(width, height, QImage::Format_MonoLSB);
    this->image.fill(Color::black);

    for (auto i = 0; i < N; i++) {
        b[i].reset(this->width, this->height);
    }

    this->timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(step()));
    this->timer->start(refresh_rate);
}

Graphics::~Graphics() { delete this->timer; }

void Graphics::step() {
    this->image.fill(this->Color::black);

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
