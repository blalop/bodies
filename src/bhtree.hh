#ifndef QUADTREE_HH
#define QUADTREE_HH

#include "body.hh"
#include "quadrant.hh"

class BHTree {

  public:
    BHTree(Quadrant quadrant);
    BHTree(const BHTree &) = default;
    ~BHTree();
    void insert(Body *body);
    void updateForce(Body *body);
    friend std::ostream &operator<<(std::ostream &s, const BHTree bhtree);

  private:
    Body *body;
    Quadrant quadrant;
    BHTree *nw, *ne, *sw, *se;
    constexpr static double THETA = 0.5;
    bool isInternal() const;
    void placeBody(Body *body);
};

#endif // QUADTREE_HH
