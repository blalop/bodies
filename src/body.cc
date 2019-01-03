#include "body.hh"

Body::Body() {
    this->x = this->y = 0;
    this->vx = this->vy = 0;
}

void Body::reset(int width, int height) {
    this->x = qrand() % width;
    this->y = qrand() % height;
    this->vx = qrand() % 3 - 1;
    this->vy = qrand() % 3 - 1;
}

QPoint Body::move() {
    this->x = this->x + this->vx;
    this->y = this->y + this->vy;
    return QPoint(this->x, this->y);
}
