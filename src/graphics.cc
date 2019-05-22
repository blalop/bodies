#include "graphics.hh"

#include "body.hh"
#include "vector2d.hh"

Graphics::Graphics(QWidget *parent, Map *map, int iters, int trace)
    : QWidget(parent), map(map), iters(iters), counter(0), trace(trace), timer(new QTimer(this)) {
    this->resize(Graphics::SIZE, Graphics::SIZE);

    this->image =
        QImage(Graphics::SIZE, Graphics::SIZE, QImage::Format_MonoLSB);
    this->image.fill(this->Color::BLACK);

    if (this->trace < this->iters && this->trace != -1) {
        this->show();
    }

    QObject::connect(this->timer.get(), SIGNAL(timeout()), this, SLOT(step()));
    this->timer->start(0);
}

void Graphics::draw() {
    this->image.fill(this->Color::BLACK);
    for (Body body : this->map->getBodies()) {
        if (body.in(this->map->getQuadrant())) {
            Vector2D<double> point = body.getPos().scale(
                Graphics::SIZE, -this->map->getQuadrant().length() / 2,
                +this->map->getQuadrant().length() / 2);

            int x = static_cast<int>(std::floor(point.x));
            int y = static_cast<int>(std::floor(point.y));

            this->image.setPixel(x, y, this->Color::WHITE);
            if (x < Graphics::SIZE - 1 && y < Graphics::SIZE - 1) {
                this->image.setPixel(x + 1, y, this->Color::WHITE);
                this->image.setPixel(x, y + 1, this->Color::WHITE);
                this->image.setPixel(x + 1, y + 1, this->Color::WHITE);
            }
        }
    }
    this->update();
}

void Graphics::step() {
    if (this->counter >= this->iters) {
        this->close();
    }

    this->map->compute();

    if (this->counter % this->trace == 0) {
        this->draw();
    }

    this->counter++;
}

void Graphics::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawImage(0, 0, this->image);
}

void Graphics::saveImage(QString filename) const {
    this->image.save(filename, "PNG");
}