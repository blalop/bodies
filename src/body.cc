#include "body.hh"

#include <QtMath>

const double G = 6.6738e-11;
const double SOLAR_MASS = 1.9884e30;
const double MIN_MASS = 1e15;
const double MAX_MASS = 1e16;
const double E = 3e4;   // softening parameter
const double DELTA = 1; // deltatime
const double DRAND_MAX = static_cast<double>(RAND_MAX);

Body::Body() : x(0), y(0), vx(0), vy(0), fx(0), fy(0) {
    double rnd = static_cast<double>(qrand());
    this->mass = (MAX_MASS - MIN_MASS) * rnd / DRAND_MAX + MIN_MASS;
}

void Body::place(int width, int height) {
    this->x = qrand() % width;
    this->y = qrand() % height;
}

void Body::addForce(Body b) {
    double dx = b.x - this->x;
    double dy = b.y - this->y;
    double r = qSqrt(dx * dx + dy * dy);
    double f = (G * this->mass * b.mass) / (r * r + E * E);
    this->fx += f * dx / r;
    this->fy += f * dy / r;
}

void Body::resetForce() { this->fx = this->fy = 0; }

QPoint Body::move() {
    this->vx += this->fx / this->mass * DELTA;
    this->vy += this->fy / this->mass * DELTA;
    this->x += this->vx;
    this->y += this->vy;
    return QPoint(this->x, this->y);
}

