#include "graphics.hh"

#include "data/vector2d.hh"

Graphics::Graphics(QWidget *parent, Vector2D<int> dim, int refresh_rate, int n)
    : QWidget(parent), dim(dim), timer(new QTimer), map(dim, n) {

    int width = dim.x();
    int height = dim.y();
    this->resize(width, height);

    this->image = QImage(width, height, QImage::Format_MonoLSB);
    this->image.fill(this->Color::black);

    QObject::connect(this->timer.get(), SIGNAL(timeout()), this, SLOT(step()));
    this->timer->start(refresh_rate);
}

Graphics::~Graphics() {}

void Graphics::step() {
    this->image.fill(this->Color::black);

    map.compute();

    std::vector<Vector2D<int>> points = map.getPositions();
    for (auto point : points) {
        int x = point.x();
        int y = point.y();

        if (x >= 0 && x < this->dim.x() && y >= 0 && y < this->dim.y()) {
            this->image.setPixel(x, y, this->Color::white);
        }
    }

    this->update();
}

void Graphics::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawImage(0, 0, this->image);
}
