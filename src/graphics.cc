#include "graphics.hh"

#include "vector2d.hh"

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
    this->image.fill(this->Color::BLACK);

    this->map.compute();
    this->drawPoints();

    if (this->itersCounter++ > this->iters) {
        this->timer->stop();
    }

    this->update();
}

void Graphics::drawPoints() {
    std::vector<Vector2D<int>> points = map.getPositions();
    for (auto point : points) {
        int x = point.x();
        int y = point.y();

        this->image.setPixel(x, y, this->Color::WHITE);
    }
}

void Graphics::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawImage(0, 0, this->image);
}
