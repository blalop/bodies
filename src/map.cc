#include "map.hh"

#if defined BHTREE || defined PARALLEL
#include "bhtree.hh"
#endif

#include "vector2d.hh"

Map::Map(double deltatime) : deltatime(deltatime) {}

std::vector<Body> Map::getBodies() const { return this->bodies; }

Quadrant Map::getQuadrant() const { return this->quadrant; }


#if BRUTE
void Map::compute() {
    for (unsigned i = 0; i < this->bodies.size(); i++) {
        this->bodies[i].resetForce();
        for (unsigned j = 0; j < this->bodies.size(); j++) {
            if (i != j) {
                this->bodies[i].computeForce(this->bodies[j]);
            }
        }
    }
    for (Body &body : this->bodies) {
        body.computeVelocity(this->deltatime);
        body.computePosition(this->deltatime);
    }
}
#elif BHTREE
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
        body.computeVelocity(this->deltatime);
        body.computePosition(this->deltatime);
    }

}
#elif PARALLEL
void Map::compute() {
}
#else
#error "Define at least one of [BRUTE, BHTREE, PARALLEL]"
#endif

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
