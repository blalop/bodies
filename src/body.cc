#include "body.hh"

constexpr double G = 6.6738e-11;
constexpr double SOLAR_MASS = 1.9884e30;
constexpr double MIN_MASS = 1e13;
constexpr double MAX_MASS = 1e17;
constexpr double E = 1;        // softening parameter
constexpr double DELTA = 0.01; // deltatime
constexpr double DRAND_MAX = static_cast<double>(RAND_MAX);

Body::Body()
    : pos(Vector2D<double>()), vel(Vector2D<double>()),
      force(Vector2D<double>()), mass(0.0) {}

void Body::set(int width, int height) {
    double m = static_cast<double>(qrand());
    this->mass = (MAX_MASS - MIN_MASS) * m / DRAND_MAX + MIN_MASS;

    double x = static_cast<double>(qrand() % width);
    double y = static_cast<double>(qrand() % height);
    this->pos = Vector2D<double>(x, y);
}

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
    this->vel = this->vel + (this->force * DELTA / this->mass);
}
void Body::computePosition() { this->pos = this->pos + (this->vel * DELTA); }

void Body::checkCollision(Body &b) {
    if (this->mass > b.mass && this->pos == b.pos) {
        this->mass += b.mass;
        b.mass = 0;
    }
}