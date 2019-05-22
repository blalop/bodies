#ifndef MAP_HH
#define MAP_HH

#include "body.hh"
#include "quadrant.hh"

#include <iostream>
#include <memory>
#include <vector>

class Map {
  public:
    Map(double deltatime);
    std::vector<Body> getBodies() const;
    Quadrant getQuadrant() const;
    virtual void compute() = 0;
    friend std::istream &operator>>(std::istream &s, Map *map);
    friend std::ostream &operator<<(std::ostream &s, const Map *map);

  protected:
    double deltatime;
    std::vector<Body> bodies;
    Quadrant quadrant;
};

class MapBrute : public Map {
  public:
    MapBrute(double deltatime);
    void compute();
};

class MapBHTree : public Map {
  public:
    MapBHTree(double deltatime);
    void compute();
};

class MapParallel : public Map {
  public:
    MapParallel(double deltatime);
    void compute();
};

#endif // MAP_HH
