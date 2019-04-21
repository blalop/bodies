#ifndef BODY_HH
#define BODY_HH

#include "quadrant.hh"
#include "vector2d.hh"

#include <iostream>

class Body {

  public:
    Body();
    Body(Vector2D<double> pos, Vector2D<double> vel, double mass);
    Vector2D<int> getPos() const;
    bool in(Quadrant q) const;
    Body operator+(const Body b) const;
    bool operator==(const Body b) const;
    double getDistanceTo(const Body b) const;
    void computeForce(const Body b);
    void computeVelocity();
    void computePosition();
    void checkCollision(Body &b);
    friend std::ostream &operator<<(std::ostream &s, const Body b);

  private:
    Vector2D<double> pos, vel, force;
    double mass;
    constexpr static double G = 6.6738e-11;
    constexpr static double E = 1;         // softening parameter
    constexpr static double DELTA = 0.001; // deltatime
};

#endif // BODY_HH
