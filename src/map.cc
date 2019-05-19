#include "map.hh"

#if defined BHTREE || defined PARALLEL
#include "bhtree.hh"
#endif

#if defined PARALLEL
#include <array>
#include <memory>
#include <thread>
#define THREADS 16
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
void buildTree(std::shared_ptr<BHTree> bhtree, std::vector<Body *> bodies) {
    for (Body *body : bodies) {
        if (body->in(bhtree->getQuadrant())) {
            bhtree->insert(*body);
        }
    }
}

void computeTree(std::shared_ptr<BHTree> bhtree, std::vector<Body *> *bodies,
                 double deltatime) {
    for (Body *body : *bodies) {
        body->resetForce();
        bhtree->updateForce(*body);
        body->computeVelocity(deltatime);
        body->computePosition(deltatime);
    }
}
void Map::compute() {
    std::array<std::vector<Body *>, THREADS> bodies;
    std::array<Quadrant, 16> quadrants = {
        this->quadrant.nw().nw(), this->quadrant.nw().ne(),
        this->quadrant.nw().sw(), this->quadrant.nw().se(),
        this->quadrant.ne().nw(), this->quadrant.ne().ne(),
        this->quadrant.ne().sw(), this->quadrant.ne().se(),
        this->quadrant.sw().nw(), this->quadrant.sw().ne(),
        this->quadrant.sw().sw(), this->quadrant.sw().se(),
        this->quadrant.se().nw(), this->quadrant.se().ne(),
        this->quadrant.se().sw(), this->quadrant.se().se()};

    for (Body &body : this->bodies) {
        for (unsigned i = 0; i < THREADS; i++) {
            if (body.in(quadrants[i])) {
                bodies[i].push_back(&body);
            }
        }
    }

    std::array<std::shared_ptr<BHTree>, THREADS> trees;

    for (unsigned i = 0; i < THREADS; i++) {
        trees[i] = std::shared_ptr<BHTree>(new BHTree(quadrants[i]));
    }

    std::array<std::thread, THREADS> buildThreads;

    for (unsigned i = 0; i < THREADS; i++) {
        buildThreads[i] = std::thread(buildTree, trees[i], bodies[i]);
    }

    for (unsigned i = 0; i < THREADS; i++) {
        buildThreads[i].join();
    }

    std::shared_ptr<BHTree> nwTree(
        new BHTree(this->quadrant, trees[0], trees[1], trees[2], trees[3]));
    std::shared_ptr<BHTree> neTree(
        new BHTree(this->quadrant, trees[4], trees[5], trees[6], trees[7]));
    std::shared_ptr<BHTree> swTree(
        new BHTree(this->quadrant, trees[8], trees[9], trees[10], trees[11]));
    std::shared_ptr<BHTree> seTree(
        new BHTree(this->quadrant, trees[12], trees[13], trees[14], trees[15]));
    std::shared_ptr<BHTree> bhtree(
        new BHTree(this->quadrant, nwTree, neTree, swTree, seTree));

    std::array<std::thread, THREADS> computeThreads;

    for (unsigned i = 0; i < THREADS; i++) {
        computeThreads[i] =
            std::thread(computeTree, bhtree, &bodies[i], this->deltatime);
    }

    for (unsigned i = 0; i < THREADS; i++) {
        computeThreads[i].join();
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
