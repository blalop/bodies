#ifndef MAP_HH
#define MAP_HH

#include "body.hh"
#include "vector2d.hh"

#include <fstream>
#include <vector>

class Map {

  public:
    Map();
    std::vector<Vector2D<int>> getPositions() const;
    void compute();
    friend std::ostream &operator<<(std::ostream &s, const Map map);
    double dim;

  private:
    std::vector<Body> map;
    int n;
};

#endif // MAP_HH
