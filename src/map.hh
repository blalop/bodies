#ifndef MAP_HH
#define MAP_HH

#include "body.hh"
#include "vector2d.hh"

#include <iostream>
#include <vector>

class Map {

  public:
    Map();
    std::vector<Vector2D<double>> getPositions() const;
    void compute();
    friend std::istream &operator>>(std::istream &s, Map &map);
    friend std::ostream &operator<<(std::ostream &s, const Map map);
    int n;
    double radius;

  private:
    std::vector<Body> map;
};

#endif // MAP_HH
