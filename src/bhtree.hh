#ifndef BHTREE_HH
#define BHTREE_HH

#include "body.hh"
#include "quadrant.hh"

#include <memory>

class BHTree {
  public:
    BHTree(Quadrant quadrant);
    BHTree(Quadrant quadrant, std::shared_ptr<BHTree> nw,
           std::shared_ptr<BHTree> ne, std::shared_ptr<BHTree> sw,
           std::shared_ptr<BHTree> se);
    ~BHTree();
    void insert(const Body body);
    void updateForce(Body &body);
    Quadrant getQuadrant() const;
    int getGroups() const;
    int getAvgSons() const;

  private:
    Body body;
    Quadrant quadrant;
    std::shared_ptr<BHTree> nw, ne, sw, se;
    int groups, avgSons;
    bool isInternal() const;
    void placeBody(Body body);
    int countSons() const;

    constexpr static double THETA = 0.5;
};

#endif // BHTREE_HH
