#include "map.hh"

#include "vector2d.hh"


// Base map
Map::Map(double deltatime) : deltatime(deltatime) {}

std::vector<Body> Map::getBodies() const { return this->bodies; }

Quadrant Map::getQuadrant() const { return this->quadrant; }

std::istream &operator>>(std::istream &s, std::shared_ptr<Map> map) {
    int n;
    double radius;
    s >> n;
    s >> radius;
    map->bodies.reserve(static_cast<unsigned int>(n));
    map->quadrant = Quadrant(radius * 2);

    for (auto i = 0; i < n; i++) {
        double m, x, y, vx, vy;
        s >> m >> x >> y >> vx >> vy;
        Vector2D<double> pos = Vector2D<double>(x, y);
        Vector2D<double> vel = Vector2D<double>(vx, vy);
        map->bodies.push_back(Body(m, pos, vel));
    }
    return s;
}

std::ostream &operator<<(std::ostream &s, const std::shared_ptr<Map> map) {
    s << "Map: ";
    s << map->bodies.size() << " " << map->quadrant.length() << std::endl;
    for (Body body : map->bodies) {
        s << body << std::endl;
    }
    return s;
}

// Brute force based map
MapBrute::MapBrute(double deltatime) : Map(deltatime) {}

void MapBrute::compute() {
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

// BHTree based map
MapBHTree::MapBHTree(double deltatime) : Map(deltatime) {}

void MapBHTree::compute() {
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

// Parallel map
MapParallel::MapParallel(double deltatime)
    : Map(deltatime), entry(MapParallel::THREADS),
      draw(MapParallel::THREADS + 1), build(MapParallel::THREADS),
      calculate(MapParallel::THREADS), bhtree(this->quadrant) {

    this->trees = {
            new BHTree(this->quadrant.nw()), new BHTree(this->quadrant.ne()),
            new BHTree(this->quadrant.sw()), new BHTree(this->quadrant.se())};
        BHTree bhtree(this->quadrant);

    this->threads.reserve(MapParallel::THREADS);
    for (int i = 0; i < MapParallel::THREADS; i++) {
        this->threads[i] = std::thread(&MapParallel::threadRoutine, this, i);
    }
}

void MapParallel::compute() { this->draw.wait(); }

void MapParallel::threadRoutine(int id) {
    while (true) {
        if (id == 0) {
            for (Body &body : this->bodies) {
                if (body.in(this->quadrant.nw())) {
                    this->qBodies[0].push_back(&body);
                } else if (body.in(this->quadrant.ne())) {
                    this->qBodies[1].push_back(&body);
                } else if (body.in(this->quadrant.sw())) {
                    this->qBodies[2].push_back(&body);
                } else if (body.in(this->quadrant.se())) {
                    this->qBodies[3].push_back(&body);
                }
            }
        }

        this->entry.wait();

        for (Body *body : this->qBodies[id]) {
            if (body->in(this->trees[id]->getQuadrant())) {
                this->trees[id]->insert(*body);
            }
        }

        this->build.wait();

        if (id == 0) {
            this->bhtree.append(trees[0], trees[1], trees[2], trees[3]);
        }

        this->calculate.wait();

        for (Body *body : this->qBodies[id]) {
            body->resetForce();
            this->bhtree.updateForce(*body);
            body->computeVelocity(this->deltatime);
            body->computePosition(this->deltatime);
        }

        this->draw.wait();
    }
}

void MapParallel::join() {
    for (int i = 0; i < MapParallel::THREADS; i++) {
        this->threads[i].join();
    }
}
