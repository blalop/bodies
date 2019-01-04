#include "body.hh"

#include <QtMath>

const double G = 6.6738e-11;
const double SOLAR_MASS = 1.9884e30;
const double DEFAULT_MASS = 1e15;
const double ERR = 3e4; // avoid inf

Body::Body() {
    this->x = this->y = 0;
    this->vx = this->vy = 0;
    this->fx = this->fy = 0;
    this->mass = DEFAULT_MASS;
}

void Body::place(int width, int height) {
    this->x = qrand() % width;
    this->y = qrand() % height;
}

void Body::addForce(Body b) {
    double dx = b.x - this->x;
    double dy = b.y - this->y;
    double dist = qSqrt(dx * dx + dy * dy);

    double F = (G * this->mass * b.mass) / (dist * dist + ERR * ERR);
    this->fx += F * dx / dist;
    this->fy += F * dy / dist;
}

void Body::resetForce() { this->fx = this->fy = 0; }

QPoint Body::move() {
    this->vx += this->fx / this->mass;
    this->vy += this->fy / this->mass;
    this->x += this->vx;
    this->y += this->vy;
    return QPoint(this->x, this->y);
}
