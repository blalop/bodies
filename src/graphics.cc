#include "graphics.hh"

Graphics::Graphics(QWidget *parent, Map map, int iters)
    : QWidget(parent), map(map), iters(iters), itersCounter(0),
      timer(new QTimer) {
    this->resize(Graphics::SIZE, Graphics::SIZE);

    this->image =
        QImage(Graphics::SIZE, Graphics::SIZE, QImage::Format_MonoLSB);
    this->image.fill(this->Color::BLACK);

    QObject::connect(this->timer.get(), SIGNAL(timeout()), this, SLOT(step()));
    this->timer->start(0);
}

void Graphics::step() {
    this->map.compute();
    this->image.fill(this->Color::BLACK);
    for (Vector2D<double> point : map.getPositions()) {
        if (Quadrant(ORIGIN, this->map.radius * 2).contains(point)) {
            point = point.scale(Graphics::SIZE, -this->map.radius,
                                +this->map.radius);
            int x = static_cast<int>(std::floor(point.x));
            int y = static_cast<int>(std::floor(point.y));
            this->image.setPixel(x, y, this->Color::WHITE);
        }
    }
    this->update();

    if (this->itersCounter++ > this->iters) {
        this->timer->stop();
    }
}

void Graphics::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawImage(0, 0, this->image);
}
