#include "bhtree.hh"

const Body EMPTY_BODY;

BHTree::BHTree(Quadrant quadrant)
    : body(EMPTY_BODY), quadrant(quadrant), groups(0), avgSons(0) {
    this->nw = this->ne = this->sw = this->se = nullptr;
}

BHTree::BHTree(Quadrant quadrant, std::shared_ptr<BHTree> nw,
               std::shared_ptr<BHTree> ne, std::shared_ptr<BHTree> sw,
               std::shared_ptr<BHTree> se)
    : quadrant(quadrant), groups(0), avgSons(0) {
    this->nw = nw;
    this->ne = ne;
    this->sw = sw;
    this->se = se;
    this->body =
        this->nw->body + this->ne->body + this->sw->body + this->se->body;
}

BHTree::~BHTree() {}

void BHTree::insert(const Body body) {
    if (this->body == EMPTY_BODY) {
        this->body = body;
    } else if (this->isInternal()) {
        this->body = this->body + body;
        this->placeBody(body);
    } else {
        this->nw = std::shared_ptr<BHTree>(new BHTree(this->quadrant.nw()));
        this->ne = std::shared_ptr<BHTree>(new BHTree(this->quadrant.ne()));
        this->sw = std::shared_ptr<BHTree>(new BHTree(this->quadrant.sw()));
        this->se = std::shared_ptr<BHTree>(new BHTree(this->quadrant.se()));
        this->placeBody(this->body);
        this->placeBody(body);
        this->body = this->body + body;
    }
}

void BHTree::updateForce(Body &body) {
    if (this->body == EMPTY_BODY || this->body == body) {
        return;
    }
    if (this->isInternal()) {
        double s = this->quadrant.length();
        double d = this->body.getDistanceTo(body);
        if (s / d < BHTree::THETA) {
            // this->groups++;
            // this->avgSons = (this->avgSons + this->countSons()) / 2;
            body.computeForce(this->body);
        } else {
            this->nw->updateForce(body);
            this->ne->updateForce(body);
            this->sw->updateForce(body);
            this->se->updateForce(body);
        }
    } else {
        body.computeForce(this->body);
    }
}

Quadrant BHTree::getQuadrant() const { return this->quadrant; }

int BHTree::getGroups() const { return this->groups; }

int BHTree::getAvgSons() const { return this->avgSons; }

int BHTree::countSons() const {
    if (this->isInternal()) {
        return this->nw->countSons() + this->ne->countSons() +
               this->sw->countSons() + this->se->countSons();
    } else {
        return 1;
    }
}

bool BHTree::isInternal() const {
    return this->nw || this->ne || this->sw || this->se;
}

void BHTree::placeBody(Body body) {
    if (body.in(this->quadrant.ne())) {
        this->ne->insert(body);
    } else if (body.in(this->quadrant.nw())) {
        this->nw->insert(body);
    } else if (body.in(this->quadrant.sw())) {
        this->sw->insert(body);
    } else if (body.in(this->quadrant.se())) {
        this->se->insert(body);
    }
}
