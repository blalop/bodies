#ifndef BODY_HH
#define BODY_HH

#include "quadrant.hh"
#include "vector2d.hh"

#include <iostream>

class Body {
  public:
    Body();
    Body(double mass, Vector2D<double> pos, Vector2D<double> vel);
    Vector2D<double> getPos() const;
    bool in(Quadrant q) const;
    double getDistanceTo(const Body b) const;
    void resetForce();
    void computeForce(const Body b);
    void computeVelocity();
    void computePosition(const double deltatime);
    Body operator+(const Body body) const;
    bool operator==(const Body body) const;
    friend std::ostream &operator<<(std::ostream &s, const Body b);

  private:
    double mass;
    Vector2D<double> pos, vel, force;
    static constexpr double G = 6.67e-11;
    static constexpr double EPS = 3e4; // softening parameter
};

#endif // BODY_HH
