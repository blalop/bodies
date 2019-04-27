#include "body.hh"

#include <iomanip>

Body::Body() : mass(0.0), pos(ORIGIN), vel(ORIGIN), force(ORIGIN) {}

Body::Body(double mass, Vector2D<double> pos, Vector2D<double> vel)
    : mass(mass), pos(pos), vel(vel), force(ORIGIN) {}

Vector2D<double> Body::getPos() const {
    return Vector2D<double>(this->pos.x, this->pos.y);
}

bool Body::in(Quadrant quadrant) const { return quadrant.contains(this->pos); }

double Body::getDistanceTo(const Body body) const {
    Vector2D<double> d = body.pos - this->pos;
    double r = d.mod();
    return r;
}

void Body::resetForce() { this->force = ORIGIN; }

void Body::computeForce(const Body body) {
    Vector2D<double> d = body.pos - this->pos;
    double r = d.mod();
    double f =
        (Body::G * this->mass * body.mass) / (r * r + Body::EPS * Body::EPS);
    this->force += d * f / r;
}

void Body::computeVelocity() { this->vel += this->force / this->mass; }

void Body::computePosition(const double deltatime) {
    this->pos += this->vel * deltatime;
}

Body Body::operator+(const Body body) const {
    double mass = this->mass + body.mass;
    Vector2D<double> pos =
        (this->pos * this->mass + body.pos * body.mass) / mass;
    Vector2D<double> vel =
        (this->vel * this->mass + body.vel * body.mass) / mass;
    return Body(mass, pos, vel);
}

bool Body::operator==(const Body body) const {
    return this->mass == body.mass && this->pos == body.pos &&
           this->vel == body.vel;
}

std::ostream &operator<<(std::ostream &s, const Body body) {
    s << "Body: " << std::setprecision(5) << body.mass << " ";
    s << body.pos << " " << body.vel << " " << body.force;
    return s;
}
