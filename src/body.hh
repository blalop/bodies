#ifndef BODY_HH
#define BODY_HH

#include <QImage>
#include <QPoint>

class Body {

  public:
    Body();
    void place(int width, int heigth);
    void addForce(Body b);
    void resetForce();
    QPoint move();

  private:
    double x, y;
    double vx, vy;
    double fx, fy;
    double mass;
};

#endif // BODY_HH
