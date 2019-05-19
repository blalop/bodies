#include "map.hh"

#if defined BHTREE || defined PARALLEL
#include "bhtree.hh"
#endif

#if defined PARALLEL
#include <memory>
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
void buildTree(std::shared_ptr<BHTree> bhtree, std::vector<Body*> bodies) {
    for (Body *body : bodies) {
        if (body->in(bhtree->getQuadrant())) {
            bhtree->insert(*body);
        }
    }
}

void computeTree(std::shared_ptr<BHTree> bhtree, std::vector<Body*> *bodies, double deltatime) {
    for (Body *body : *bodies) {
        body->resetForce();
        bhtree->updateForce(*body);
        body->computeVelocity(deltatime);
        body->computePosition(deltatime);
    }
}
void Map::compute() {
    std::vector<Body*> nwBodies, neBodies, swBodies, seBodies;

    for (Body &body : this->bodies) {
        if (body.in(this->quadrant.nw())) {
            nwBodies.push_back(&body);
        } else if (body.in(this->quadrant.ne())) {
            neBodies.push_back(&body);
        } else if (body.in(this->quadrant.sw())) {
            swBodies.push_back(&body);
        } else if (body.in(this->quadrant.se())) {
            seBodies.push_back(&body);
        }
    }

    std::shared_ptr<BHTree> nwTree(new BHTree(this->quadrant.nw()));
    std::shared_ptr<BHTree> neTree(new BHTree(this->quadrant.ne()));
    std::shared_ptr<BHTree> swTree(new BHTree(this->quadrant.sw()));
    std::shared_ptr<BHTree> seTree(new BHTree(this->quadrant.se()));

    std::thread nwThreadBuild(buildTree, nwTree, nwBodies);
    std::thread neThreadBuild(buildTree, neTree, neBodies);
    std::thread swThreadBuild(buildTree, swTree, swBodies);
    std::thread seThreadBuild(buildTree, seTree, seBodies);

    nwThreadBuild.join();
    neThreadBuild.join();
    swThreadBuild.join();
    seThreadBuild.join();

    std::shared_ptr<BHTree> bhtree(new BHTree(this->quadrant, nwTree, neTree, swTree, seTree));

    std::thread nwThreadCompute(computeTree, bhtree, &nwBodies, this->deltatime);
    std::thread neThreadCompute(computeTree, bhtree, &neBodies, this->deltatime);
    std::thread swThreadCompute(computeTree, bhtree, &swBodies, this->deltatime);
    std::thread seThreadCompute(computeTree, bhtree, &seBodies, this->deltatime);

    nwThreadCompute.join();
    neThreadCompute.join();
    swThreadCompute.join();
    seThreadCompute.join();
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
