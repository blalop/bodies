#include "map.hh"

#include "bhtree.hh"
#include "vector2d.hh"

Map::Map(double deltatime) : deltatime(deltatime) {}

std::vector<Body> Map::getBodies() const { return this->bodies; }

Quadrant Map::getQuadrant() const { return this->quadrant; }

void Map::compute() {
    BHTree bhtree(this->quadrant);
    for (Body body : this->bodies) {
        if (body.in(this->quadrant)) {
            bhtree.insert(body);
        }
    }

    for (Body &body : this->bodies) {
        body.resetForce();
        bhtree.updateForce(body);
        body.computeVelocity();
        body.computePosition(this->deltatime);
    }
}

std::istream &operator>>(std::istream &s, Map &map) {
    int n;
    double radius;
    s >> n;
    s >> radius;
    map.bodies.reserve(static_cast<unsigned int>(n));
    map.quadrant = Quadrant(radius * 2);

    for (auto i = 0; i < n; i++) {
        double m, x, y, vx, vy;
        s >> m >> x >> y >> vx >> vy;
        Vector2D<double> pos = Vector2D<double>(x, y);
        Vector2D<double> vel = Vector2D<double>(vx, vy);
        map.bodies.push_back(Body(m, pos, vel));
    }
    return s;
}

std::ostream &operator<<(std::ostream &s, const Map map) {
    s << "Map: ";
    s << map.bodies.size() << " " << map.quadrant.length() << std::endl;
    for (Body body : map.bodies) {
        s << body << std::endl;
    }
    return s;
}
