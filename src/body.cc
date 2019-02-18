#include "body.hh"

#include <utility>

constexpr double G = 6.6738e-11;
constexpr double E = 1; // softening parameter
constexpr double DELTA = 0.001; // deltatime

Body::Body() : pos(ORIGIN), vel(ORIGIN), force(ORIGIN), mass(0.0) {}

Body::Body(Vector2D<double> pos, Vector2D<double> vel, double mass)
    : pos(pos), vel(vel), force(ORIGIN), mass(mass) {}

Vector2D<int> Body::getPos() const {
    return Vector2D<int>(this->pos.x(), this->pos.y());
}

bool Body::inMap(Vector2D<int> limits) const {
    int x = this->pos.x();
    int y = this->pos.y();
    return x >= 0 && x < limits.x() && y >= 0 && y < limits.y();
}

void Body::resetForce() { this->force = Vector2D<double>(); }

void Body::computeForce(const Body b) {
    Vector2D<double> d = b.pos - this->pos;
    double r = d.mod();
    double f = (G * this->mass * b.mass) / (r * r + E * E);
    this->force = this->force + d * f / r;
}

void Body::computeVelocity() {
    this->vel = this->vel + this->force * DELTA / this->mass;
}
void Body::computePosition() { this->pos = this->pos + (this->vel * DELTA); }

void Body::checkCollision(Body &b) {
    if (this->mass > b.mass && this->pos == b.pos) {
        this->mass += b.mass;
        b.mass = 0;
    }
    // if (this->pos == b.pos) std::swap(this->vel, b.vel);
}