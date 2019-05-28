#ifndef MAP_HH
#define MAP_HH

#include "barrier.hh"
#include "bhtree.hh"
#include "body.hh"
#include "quadrant.hh"


#include <array>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

class Map {
  public:
    Map(double deltatime);
    std::vector<Body> getBodies() const;
    Quadrant getQuadrant() const;
    virtual void compute() = 0;
    friend std::istream &operator>>(std::istream &s, std::shared_ptr<Map> map);
    friend std::ostream &operator<<(std::ostream &s,
                                    const std::shared_ptr<Map> map);

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
    void threadRoutine(int id);
    void join();

  private:
    std::vector<std::thread> threads;
    static constexpr int THREADS = 4;
    Barrier entry, draw, build, calculate;
    std::array<BHTree *, MapParallel::THREADS> trees;
    std::array<std::vector<Body *>, MapParallel::THREADS> qBodies;

    BHTree bhtree;
};

#endif // MAP_HH
