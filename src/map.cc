#include "map.hh"

#if defined BHTREE || defined PARALLEL
#include "bhtree.hh"
#endif

#if defined PARALLEL
#include <thread>
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
void buildTree(BHTree *bhtree, std::vector<Body> bodies) {
    for (Body body : bodies) {
        if (body.in(bhtree->getQuadrant())) {
            bhtree->insert(body);
        }
    }
}

void Map::compute() {
    BHTree *nwTree = new BHTree(this->quadrant.nw());
    BHTree *neTree = new BHTree(this->quadrant.ne());
    BHTree *swTree = new BHTree(this->quadrant.sw());
    BHTree *seTree = new BHTree(this->quadrant.se());

    std::vector<Body> nwBodies, neBodies, swBodies, seBodies;

    for (Body body : this->bodies) {
        if (body.in(this->quadrant.nw())) {
            nwBodies.push_back(body);
        } else if (body.in(this->quadrant.ne())) {
            neBodies.push_back(body);
        } else if (body.in(this->quadrant.sw())) {
            swBodies.push_back(body);
        } else if (body.in(this->quadrant.se())) {
            seBodies.push_back(body);
        } 
    }

    std::thread nwThread(buildTree, nwTree, nwBodies);
    std::thread neThread(buildTree, neTree, neBodies);
    std::thread swThread(buildTree, swTree, swBodies);
    std::thread seThread(buildTree, seTree, seBodies);

    nwThread.join();
    neThread.join();
    swThread.join();
    seThread.join();

    BHTree bhtree(this->quadrant, nwTree, neTree, swTree, seTree);

    for (Body &body : this->bodies) {
        body.resetForce();
        bhtree.updateForce(body);
        body.computeVelocity(this->deltatime);
        body.computePosition(this->deltatime);
    }
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
