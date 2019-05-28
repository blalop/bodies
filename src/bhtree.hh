#ifndef QUADTREE_HH
#define QUADTREE_HH

#include "body.hh"
#include "quadrant.hh"

#include <memory>

class BHTree {
  public:
    BHTree(Quadrant quadrant);
    ~BHTree();
    void append(BHTree *nw, BHTree *ne, BHTree *sw, BHTree *se);
    void insert(const Body body);
    void updateForce(Body &body) const;
    Quadrant getQuadrant() const;

  //private:
    Body body;
    Quadrant quadrant;
    BHTree *nw, *ne, *sw, *se;
    bool isInternal() const;
    void placeBody(Body body);

    constexpr static double THETA = 0.5;
};

#endif // QUADTREE_HH
