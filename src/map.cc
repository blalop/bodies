#include "map.hh"

#include "vector2d.hh"

// Base map
Map::Map(double deltatime, int iters) : deltatime(deltatime), iters(iters) {
    std::cin >> this;
}

Map::~Map() {}

std::vector<Body> Map::getBodies() const { return this->bodies; }

Quadrant Map::getQuadrant() const { return this->quadrant; }

std::istream &operator>>(std::istream &s, Map *map) {
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

std::ostream &operator<<(std::ostream &s, Map *map) {
    s << "Map: ";
    s << map->bodies.size() << " " << map->quadrant.length() << std::endl;
    for (Body body : map->bodies) {
        s << body << std::endl;
    }
    return s;
}

// Brute force based map
MapBrute::MapBrute(double deltatime, int iters) : Map(deltatime, iters) {}

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
MapBHTree::MapBHTree(double deltatime, int iters) : Map(deltatime, iters) {}

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
MapParallel::MapParallel(double deltatime, int iters)
    : Map(deltatime, iters), entryBarrier(MapParallel::THREADS + 1),
      sortBarrier(MapParallel::THREADS + 1),
      buildBarrier(MapParallel::THREADS),
      computeBarrier(MapParallel::THREADS + 1) {

    this->trees = {std::shared_ptr<BHTree>(new BHTree(this->quadrant.nw())),
                   std::shared_ptr<BHTree>(new BHTree(this->quadrant.ne())),
                   std::shared_ptr<BHTree>(new BHTree(this->quadrant.sw())),
                   std::shared_ptr<BHTree>(new BHTree(this->quadrant.se()))};

    this->i = 0;
    for (int i = 0; i < MapParallel::THREADS; i++) {
        this->threads.push_back(
            std::thread(&MapParallel::threadRoutine, this, i));
    }
}

MapParallel::~MapParallel() {
    for (std::thread &thread : this->threads) {
        thread.join();
    }
}

void MapParallel::compute() {
    this->entryBarrier.wait();

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

    this->trees[0].reset(new BHTree(this->quadrant.nw()));
    this->trees[1].reset(new BHTree(this->quadrant.ne()));
    this->trees[2].reset(new BHTree(this->quadrant.sw()));
    this->trees[3].reset(new BHTree(this->quadrant.se()));
    this->i++;

    this->sortBarrier.wait();

    this->computeBarrier.wait();
}

void MapParallel::threadRoutine(int id) {
    auto buildTree = [](std::shared_ptr<BHTree> bhtree, std::vector<Body *> bodies) {
        for (Body *body : bodies) {
            if (body->in(bhtree->getQuadrant())) {
                bhtree->insert(*body);
            }
        }
    };

    auto computeTree = [](BHTree bhtree, std::vector<Body *> *bodies, double deltatime) {
        for (Body *body : *bodies) {
            body->resetForce();
            bhtree.updateForce(*body);
            body->computeVelocity(deltatime);
            body->computePosition(deltatime);
        }
    };

    while (this->i < this->iters) {
        this->entryBarrier.wait();
        this->sortBarrier.wait();
        buildTree(this->trees[id], this->qBodies[id]);
        this->buildBarrier.wait();

        BHTree bhtree(this->quadrant, this->trees[0], this->trees[1], this->trees[2], this->trees[3]);
        computeTree(bhtree, &this->qBodies[id], this->deltatime);
        this->computeBarrier.wait();

        this->qBodies[id].clear();
    }
}
