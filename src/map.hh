#ifndef MAP_HH
#define MAP_HH

#include "body.hh"
#include "data/vector2d.hh"

#include <QVector>

class Map {

  public:
    Map(Vector2D<int> dim, int n);
    QVector<Vector2D<int>> getPositions() const;
    void compute();

  private:
    QVector<Body> pMap;
    Vector2D<int> dim;

    void computeForces();
    void computeVelocities();
    void computePositions();
};

#endif // MAP_HH