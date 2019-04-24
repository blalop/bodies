#include "map.hh"

#include "bhtree.hh"
#include "vector2d.hh"

Map::Map() {
    std::cin >> this->n;
    std::cin >> this->dim;
    this->map.reserve(n);

    for (auto i = 0; i < n; i++) {
        double m, x, y, vx, vy;
        std::cin >> m >> x >> y >> vx >> vy;
        Vector2D<double> pos = Vector2D<double>(x, y);
        Vector2D<double> vel = Vector2D<double>(vx, vy);

        this->map.push_back(Body(m, pos, vel));
    }
}

std::vector<Vector2D<int>> Map::getPositions() const {
    std::vector<Vector2D<int>> points(this->map.size());
    for (auto body : this->map) {
        Vector2D<int> p = body.getPos();
        points.push_back(p);
    }
    return points;
}

void Map::compute() {
    Quadrant quadrant = Quadrant(Vector2D<double>(0, 0), dim);
    BHTree *bhtree = new BHTree(quadrant);
    for (auto &body : this->map) {
        if (body.in(quadrant)) {
            bhtree->insert(&body);
        }
    }

    for (auto &body : this->map) {
        bhtree->updateForce(&body);
        body.computeVelocity();
        body.computePosition();
    }
}

std::ostream &operator<<(std::ostream &s, const Map map) {
    s << map.n << std::endl;
    for (auto body : map.map) {
        s << body << std::endl;
    }
    return s;
}
