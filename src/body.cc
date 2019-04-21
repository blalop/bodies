#include "body.hh"

#include <iomanip>
#include <utility>

const Vector2D<double> ORIGIN = Vector2D<double>(0, 0);

Body::Body() : pos(ORIGIN), vel(ORIGIN), force(ORIGIN), mass(0.0) {}

Body::Body(Vector2D<double> pos, Vector2D<double> vel, double mass)
    : pos(pos), vel(vel), force(ORIGIN), mass(mass) {}

Vector2D<int> Body::getPos() const {
    return Vector2D<int>(this->pos.x(), this->pos.y());
}

bool Body::in(Quadrant q) const { return q.contains(this->pos); }

Body Body::operator+(const Body b) const {
    Body n = Body();
    n.pos = (this->pos + b.pos) / 2;
    n.vel = this->vel + b.vel;
    n.force = this->force + b.force;
    n.mass = this->mass + b.mass;
    return n;
}

double Body::getDistanceTo(const Body b) const {
    Vector2D<double> d = b.pos - this->pos;
    double r = d.mod();
    return r;
}

void Body::computeForce(const Body b) {
    Vector2D<double> d = b.pos - this->pos;
    double r = d.mod();
    double f = (Body::G * this->mass * b.mass) / (r * r + E * E);
    this->force = this->force + d * f / r;
}

void Body::computeVelocity() {
    this->vel = this->vel + this->force * Body::DELTA / this->mass;
}
void Body::computePosition() {
    this->pos = this->pos + (this->vel * Body::DELTA);
}

void Body::checkCollision(Body &b) {
    if (this->mass > b.mass && this->pos == b.pos) {
        this->mass += b.mass;
        b.mass = 0;
    }
    // if (this->pos == b.pos) std::swap(this->vel, b.vel);
}

bool Body::operator==(const Body b) const {
    return this->pos == b.pos && this->vel == b.vel && this->force == b.force &&
           this->mass == b.mass;
}

std::ostream &operator<<(std::ostream &s, const Body b) {
    using std::endl;
    using std::fixed;
    using std::setprecision;
    using std::setw;
    auto precision = s.precision();
    auto width = s.width();
    s << "Body:" << endl;
    s << "\tmass: " << fixed << setw(width) << setprecision(precision) << b.mass
      << endl;
    s << "\tpos: " << b.pos << endl;
    s << "\tvel: " << b.vel << endl;
    s << "\tforce: " << b.force << endl;
    return s;
}
