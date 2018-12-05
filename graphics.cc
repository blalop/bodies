#include "graphics.hh"

graphics::graphics(QWidget *parent, int height, int width) : QWidget(parent) {
    this->resize(height, width);
    this->image = QImage(height, width, QImage::Format_Mono);
    this->image.fill(0);
}

graphics::~graphics() {}

void graphics::refresh(QImage image) {
    this->image.swap(image);
    QWidget::update();
}

void graphics::paintEvent() {
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}
