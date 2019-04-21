#ifndef MAP_HH
#define MAP_HH

#include "body.hh"
#include "vector2d.hh"

#include <vector>

class Map {

  public:
    Map(double dim, int n);
    std::vector<Vector2D<int>> getPositions() const;
    void compute();

  private:
    std::vector<Body> pMap;
    double dim;
    constexpr static double SOLAR_MASS = 1.9884e30;
    constexpr static double MIN_MASS = 1e13;
    constexpr static double MAX_MASS = 1e17;
};

#endif // MAP_HH