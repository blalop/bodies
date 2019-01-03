#ifndef BODY_HH
#define BODY_HH

#include <QImage>
#include <QPoint>

class Body {

  public:
    Body();
    void reset(int width, int heigth);
    QPoint move();

  private:
    int x, y;
    int vx, vy;
};

#endif // BODY_HH
