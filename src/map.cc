#include "map.hh"

#include "bhtree.hh"
#include "vector2d.hh"

#include <cstdlib>

Map::Map(double dim, int n) : dim(dim) {
    constexpr double DRAND_MAX = static_cast<double>(RAND_MAX);
    for (auto i = 0; i < n; i++) {
        double m = static_cast<double>(std::rand());
        double mass =
            (Map::MAX_MASS - Map::MIN_MASS) * m / DRAND_MAX + Map::MIN_MASS;

        double x = static_cast<double>(std::rand() % static_cast<int>(dim));
        double y = static_cast<double>(std::rand() % static_cast<int>(dim));
        Vector2D<double> pos = Vector2D<double>(x, y);

        double vx = static_cast<double>(std::rand() % 3 - 1);
        double vy = static_cast<double>(std::rand() % 3 - 1);
        Vector2D<double> vel = Vector2D<double>(vx, vy);

        pMap.push_back(Body(pos, vel, mass));
    }
}

std::vector<Vector2D<int>> Map::getPositions() const {
    std::vector<Vector2D<int>> points(this->pMap.size());
    for (auto body : this->pMap) {
        Vector2D<int> p = body.getPos();
        points.push_back(p);
    }
    return points;
}

void Map::compute() {
    Quadrant quadrant = Quadrant(Vector2D<double>(0, 0), dim);
    BHTree *bhtree = new BHTree(quadrant);
    for (auto &body : this->pMap) {
        if (body.in(quadrant)) {
            bhtree->insert(&body);
        }
    }

    for (auto &body : this->pMap) {
        bhtree->updateForce(&body);
        body.computeVelocity();
        body.computePosition();
    }
}
