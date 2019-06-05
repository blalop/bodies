#include "quadrant.hh"

Quadrant::Quadrant() : center(ORIGIN), dim(0.0) {}

Quadrant::Quadrant(double dim) : center(ORIGIN), dim(dim) {}

Quadrant::Quadrant(Vector2D<double> center, double dim)
    : center(center), dim(dim) {}

bool Quadrant::contains(Vector2D<double> point) const {
    double radius = this->dim / 2;
    return point.x > this->center.x - radius &&
           point.y > this->center.y - radius &&
           point.x <= this->center.x + radius &&
           point.y <= this->center.y + radius;
}

double Quadrant::length() const { return this->dim; }

Quadrant Quadrant::nw() const {
    double x = this->center.x - this->dim / 4;
    double y = this->center.y - this->dim / 4;
    return Quadrant(Vector2D<double>(x, y), this->dim / 2);
}

Quadrant Quadrant::ne() const {
    double x = this->center.x + this->dim / 4;
    double y = this->center.y - this->dim / 4;
    return Quadrant(Vector2D<double>(x, y), this->dim / 2);
}

Quadrant Quadrant::sw() const {
    double x = this->center.x - this->dim / 4;
    double y = this->center.y + this->dim / 4;
    return Quadrant(Vector2D<double>(x, y), this->dim / 2);
}

Quadrant Quadrant::se() const {
    double x = this->center.x + this->dim / 4;
    double y = this->center.y + this->dim / 4;
    return Quadrant(Vector2D<double>(x, y), this->dim / 2);
}

std::ostream &operator<<(std::ostream &s, const Quadrant b) {
    std::cout << b.center << " : " << b.dim;
    return s;
}
