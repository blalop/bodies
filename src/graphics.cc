#include "graphics.hh"

#include "vector2d.hh"

Graphics::Graphics(QWidget *parent, double dim, int n, int i)
    : QWidget(parent), dim(dim), map(dim, n), iters(i), itersCounter(0),
      timer(new QTimer) {

    this->resize(dim, dim);

    this->image = QImage(dim, dim, QImage::Format_MonoLSB);
    this->image.fill(this->Color::black);

    QObject::connect(this->timer.get(), SIGNAL(timeout()), this, SLOT(step()));
    this->timer->start(0);
}

void Graphics::step() {
    this->image.fill(this->Color::black);

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

        if (x >= 0 && x < this->dim && y >= 0 && y < this->dim) {
            this->image.setPixel(x, y, this->Color::white);
        }
    }
}

void Graphics::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawImage(0, 0, this->image);
}
