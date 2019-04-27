#ifndef MAP_HH
#define MAP_HH

#include "body.hh"
#include "quadrant.hh"

#include <iostream>
#include <vector>

class Map {
  public:
    Map(double deltatime);
    std::vector<Body> getBodies() const;
    Quadrant getQuadrant() const;
    void compute();
    friend std::istream &operator>>(std::istream &s, Map &map);
    friend std::ostream &operator<<(std::ostream &s, const Map map);

  private:
    double deltatime;
    std::vector<Body> bodies;
    Quadrant quadrant;
};

#endif // MAP_HH
