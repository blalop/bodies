#include "quadrant.hh"

#include "vector2d.hh"

Quadrant::Quadrant() {
    this->dim = 0;
    this->origin = Vector2D<double>(0, 0);
}

Quadrant::Quadrant(Vector2D<double> origin, double dim) {
    this->origin = origin;
    this->dim = dim;
}
bool Quadrant::contains(Vector2D<double> point) const {
    double x = point.x();
    double y = point.y();
    return x > this->origin.x() && y > this->origin.y() &&
           x <= this->origin.x() + this->dim &&
           y <= this->origin.y() + this->dim;
}

double Quadrant::length() const { return this->dim; }

Quadrant Quadrant::nw() const {
    Quadrant q = Quadrant(this->origin, this->dim / 2);
    return q;
}

Quadrant Quadrant::ne() const {
    Vector2D<double> origin =
        Vector2D<double>(this->origin.x() + dim / 2, this->origin.y());
    Quadrant q = Quadrant(origin, this->dim / 2);
    return q;
}

Quadrant Quadrant::sw() const {
    Vector2D<double> origin =
        Vector2D<double>(this->origin.x(), this->origin.y() + dim / 2);
    Quadrant q = Quadrant(origin, this->dim / 2);
    return q;
}

Quadrant Quadrant::se() const {
    Vector2D<double> origin = Vector2D<double>(this->origin.x() + dim / 2,
                                               this->origin.y() + dim / 2);
    Quadrant q = Quadrant(origin, this->dim / 2);
    return q;
}