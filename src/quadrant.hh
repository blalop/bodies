#ifndef QUADRANT_HH
#define QUADRANT_HH

#include "vector2d.hh"

class Quadrant {

  public:
    Quadrant();
    Quadrant(double dim);
    Quadrant(Vector2D<double> center, double dim);
    bool contains(Vector2D<double> point) const;
    double length() const;
    Quadrant nw() const;
    Quadrant ne() const;
    Quadrant sw() const;
    Quadrant se() const;

  private:
    Vector2D<double> center;
    double dim;
};

#endif
