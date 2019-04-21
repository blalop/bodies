#ifndef QUADRANT_HH
#define QUADRANT_HH

#include "vector2d.hh"

class Quadrant {

  public:
    Quadrant();
    Quadrant(Vector2D<double> origin, double dim);
    bool contains(Vector2D<double> point) const;
    double length() const;
    Quadrant nw() const;
    Quadrant ne() const;
    Quadrant sw() const;
    Quadrant se() const;

  private:
    double dim;
    Vector2D<double> origin;
};

#endif