#include "map.hh"

#include "bhtree.hh"
#include "vector2d.hh"

Map::Map() : n(0), radius(0.0) {}

std::vector<Vector2D<double>> Map::getPositions() const {
    std::vector<Vector2D<double>> points(static_cast<unsigned int>(this->n));
    for (Body body : this->map) {
        Vector2D<double> p = body.getPos();
        points.push_back(p);
    }
    return points;
}

void Map::compute() {
    Quadrant quadrant = Quadrant(ORIGIN, this->radius * 2);
    BHTree *bhtree = new BHTree(quadrant);
    for (Body &body : this->map) {
        if (body.in(quadrant)) {
            bhtree->insert(&body);
        }
    }

    for (Body &body : this->map) {
        bhtree->updateForce(&body);
        body.computeVelocity();
        body.computePosition();
    }
}

std::istream &operator>>(std::istream &s, Map &map) {
    s >> map.n;
    s >> map.radius;
    map.map.reserve(static_cast<unsigned int>(map.n));

    for (auto i = 0; i < map.n; i++) {
        double m, x, y, vx, vy;
        s >> m >> x >> y >> vx >> vy;
        Vector2D<double> pos = Vector2D<double>(x, y);
        Vector2D<double> vel = Vector2D<double>(vx, vy);
        map.map.push_back(Body(m, pos, vel));
    }
    return s;
}

std::ostream &operator<<(std::ostream &s, const Map map) {
    s << map.n << std::endl;
    s << map.radius << std::endl;
    for (Body body : map.map) {
        s << body;
    }
    return s;
}
