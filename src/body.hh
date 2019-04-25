#ifndef BODY_HH
#define BODY_HH

#include "quadrant.hh"
#include "vector2d.hh"

#include <iostream>

class Body {

  public:
    Body();
    Body(double mass, Vector2D<double> pos, Vector2D<double> vel);
    Body(double mass, Vector2D<double> pos, Vector2D<double> vel,
         Vector2D<double> force);
    Body operator+(const Body b) const;
    Vector2D<double> getPos() const;
    bool in(Quadrant q) const;
    double getDistanceTo(const Body b) const;
    void computeForce(const Body b);
    void computeVelocity();
    void computePosition();
    friend std::ostream &operator<<(std::ostream &s, const Body b);

  private:
    double mass;
    Vector2D<double> pos, vel, force;
    static constexpr double G = 6.6738e-11;
    static constexpr double EPS = 1;       // softening parameter
    static constexpr double DELTA = 0.001; // deltatime
};

#endif // BODY_HH
