#ifndef BODY_HH
#define BODY_HH

#include "data/vector2d.hh"

class Body {

  public:
    Body();
    void set(int width, int height);
    Vector2D<int> getPos() const;
    bool inMap(Vector2D<int> dim) const;

    void resetForce();
    void computeForce(const Body b);
    void computeVelocity();
    void computePosition();
    void checkCollision(Body &b);

  private:
    Vector2D<double> pos, vel, force;
    double mass;
};

#endif // BODY_HH
