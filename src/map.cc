#include "map.hh"

Map::Map(Vector2D<int> dim, int n) : pMap(n, Body()), dim(dim) {
    for (auto &body : pMap) {
        body.set(dim.x(), dim.y());
    }
}

QVector<Vector2D<int>> Map::getPositions() const {
    QVector<Vector2D<int>> points(this->pMap.size());
    for (auto body : this->pMap) {
        Vector2D<int> p = body.getPos();
        points.append(p);
    }
    return points;
}

void Map::compute() {
    computeForces();
    computeVelocities();
    computePositions();
}

void Map::computeForces() {
    for (auto i = 0; i < this->pMap.size(); i++) {
        this->pMap[i].resetForce();
        for (auto j = 0; j < this->pMap.size(); j++) {
            if (i != j) {
                this->pMap[i].computeForce(this->pMap[j]);
                this->pMap[i].checkCollision(this->pMap[j]);
            }
        }
    }
}

void Map::computeVelocities() {
    for (auto &body : this->pMap) {
        body.computeVelocity();
    }
}

void Map::computePositions() {
    for (auto &body : this->pMap) {
        body.computePosition();
    }
}
