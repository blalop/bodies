#ifndef QUADTREE_HH
#define QUADTREE_HH

#include "body.hh"
#include "quadrant.hh"

class BHTree {
  public:
    BHTree(Quadrant quadrant);
    ~BHTree();
    void insert(const Body body);
    void updateForce(Body &body);

  private:
    Body body;
    Quadrant quadrant;
    BHTree *nw, *ne, *sw, *se;
    bool isInternal() const;
    void placeBody(Body body);

    constexpr static double THETA = 0.5;
};

#endif // QUADTREE_HH
