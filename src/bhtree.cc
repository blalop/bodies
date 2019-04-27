#include "bhtree.hh"

const Body EMPTY_BODY;

BHTree::BHTree(Quadrant quadrant) : body(EMPTY_BODY), quadrant(quadrant) {
    this->nw = this->ne = this->sw = this->se = nullptr;
}

BHTree::~BHTree() {
    delete this->nw;
    delete this->ne;
    delete this->sw;
    delete this->se;
}

void BHTree::insert(const Body body) {
    if (this->body == EMPTY_BODY) {
        this->body = body;
    } else if (this->isInternal()) {
        this->body = this->body + body;
        this->placeBody(body);
    } else {
        this->nw = new BHTree(this->quadrant.nw());
        this->ne = new BHTree(this->quadrant.ne());
        this->sw = new BHTree(this->quadrant.sw());
        this->se = new BHTree(this->quadrant.se());
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
