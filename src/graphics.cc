#include "graphics.hh"

#include "body.hh"
#include "vector2d.hh"

Graphics::Graphics(QWidget *parent, Map map, int iters, bool bigger)
    : QWidget(parent), map(map), iters(iters), counter(0), bigger(bigger) {
    this->resize(Graphics::SIZE, Graphics::SIZE);

    this->image =
        QImage(Graphics::SIZE, Graphics::SIZE, QImage::Format_MonoLSB);
    this->image.fill(this->Color::BLACK);

    this->timer = new QTimer(this);
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(step()));
    this->timer->start(0);
}

Graphics::~Graphics() { delete this->timer; }

void Graphics::step() {
    if (this->counter++ >= this->iters) {
        this->close();
    }

    this->map.compute();
    this->image.fill(this->Color::BLACK);
    for (Body body : map.getBodies()) {
        if (body.in(map.getQuadrant())) {
            Vector2D<double> point = body.getPos().scale(
                Graphics::SIZE, 
                -this->map.getQuadrant().length() / 2,
                +this->map.getQuadrant().length() / 2
                );

            int x = static_cast<int>(std::floor(point.x));
            int y = static_cast<int>(std::floor(point.y));

            this->image.setPixel(x, y, this->Color::WHITE);
            if (this->bigger && x < Graphics::SIZE-1 && y < Graphics::SIZE-1) {
                this->image.setPixel(x + 1, y, this->Color::WHITE);
                this->image.setPixel(x, y + 1, this->Color::WHITE);
                this->image.setPixel(x + 1, y + 1, this->Color::WHITE);
            }
        }
    }
    this->update();
}

void Graphics::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawImage(0, 0, this->image);
}

void Graphics::saveImage(QString filename) const {
    this->image.save(filename, "PNG");
}