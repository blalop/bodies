#include "body.hh"

#include <iomanip>

const Vector2D<double> ORIGIN = Vector2D<double>(0, 0);

Body::Body() : mass(0.0), pos(ORIGIN), vel(ORIGIN), force(ORIGIN) {}

Body::Body(double mass, Vector2D<double> pos, Vector2D<double> vel)
    : mass(mass), pos(pos), vel(vel), force(ORIGIN) {}

Body::Body(double mass, Vector2D<double> pos, Vector2D<double> vel,
           Vector2D<double> force)
    : mass(mass), pos(pos), vel(vel), force(force) {}

Body Body::operator+(const Body body) const {
    double mass = this->mass + body.mass;
    Vector2D<double> pos = (this->pos + body.pos) / 2;
    Vector2D<double> vel = this->vel + body.vel;
    Vector2D<double> force = this->force + body.force;
    return Body(mass, pos, vel, force);
}

Vector2D<int> Body::getPos() const {
    return Vector2D<int>(this->pos.x(), this->pos.y());
}

bool Body::in(Quadrant quadrant) const { return quadrant.contains(this->pos); }

double Body::getDistanceTo(const Body body) const {
    Vector2D<double> d = body.pos - this->pos;
    double r = d.mod();
    return r;
}

void Body::computeForce(const Body body) {
    Vector2D<double> d = body.pos - this->pos;
    double r = d.mod();
    double f =
        (Body::G * this->mass * body.mass) / (r * r + Body::EPS * Body::EPS);
    this->force += d * f / r;
}

void Body::computeVelocity() { this->vel += this->force / this->mass; }
void Body::computePosition() { this->pos += this->vel * Body::DELTA; }

std::ostream &operator<<(std::ostream &s, const Body body) {
    s << std::setprecision(2) << body.mass;
    s << body.pos << body.vel << body.force << std::endl;
    return s;
}
