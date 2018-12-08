#include "graphics.hh"

Graphics::Graphics(QWidget *parent, int height, int width) : QWidget(parent) {
    this->resize(height, width);
    this->image = QImage(height, width, QImage::Format_MonoLSB);
    this->image.fill(Color::black);
}

Graphics::~Graphics() {}

void Graphics::refresh(QImage image) {
    this->image.swap(image);
    QWidget::update();
}

void Graphics::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawImage(0, 0, this->image);
}
