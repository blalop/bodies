#include "bhtree.hh"

#include "body.hh"
#include "quadrant.hh"

BHTree::BHTree(Quadrant quadrant) {
    this->quadrant = quadrant;
    this->nw = this->ne = this->sw = this->se = nullptr;
    body = nullptr;
}

BHTree::~BHTree() {
    if (!this->isInternal()) {
        delete this;
    } else {
        if (this->nw) {
            this->nw->~BHTree();
        }
        if (this->ne) {
            this->ne->~BHTree();
        }
        if (this->sw) {
            this->sw->~BHTree();
        }
        if (this->se) {
            this->se->~BHTree();
        }
    }
}

void BHTree::insert(Body *body) {
    if (!this->body) {
        this->body = body;
    } else if (this->isInternal()) {
        Body b = *this->body + *body;
        this->body = &b;
        this->placeBody(body);
    } else {
        this->nw = new BHTree(this->quadrant.nw());
        this->ne = new BHTree(this->quadrant.ne());
        this->sw = new BHTree(this->quadrant.sw());
        this->se = new BHTree(this->quadrant.se());
        this->placeBody(body);
        this->placeBody(this->body);
        Body b = *this->body + *body;
        this->body = &b;
    }
}

void BHTree::updateForce(Body *body) {
    if (!this->body || *(this->body) == *body) {
        return;
    }
    if (this->isInternal()) {
        double s = this->quadrant.length();
        double d = this->body->getDistanceTo(*body);
        if (s / d < BHTree::THETA) {
            this->body->computeForce(*body);
        } else {
            this->nw->updateForce(body);
            this->ne->updateForce(body);
            this->sw->updateForce(body);
            this->se->updateForce(body);
        }
    } else {
        this->body->computeForce(*body);
    }
}

bool BHTree::isInternal() const {
    return this->nw || this->ne || this->sw || this->se;
}

void BHTree::placeBody(Body *body) {
    if (body->in(this->quadrant.ne())) {
        this->ne->insert(body);
    } else if (body->in(this->quadrant.nw())) {
        this->nw->insert(body);
    } else if (body->in(this->quadrant.sw())) {
        this->sw->insert(body);
    } else if (body->in(this->quadrant.se())) {
        this->se->insert(body);
    } else {
        std::exit(1);
    }
}

std::ostream &operator<<(std::ostream &s, const BHTree bhtree) {
    using std::endl;
    s << (bhtree.isInternal() ? "Internal" : "External") << " node" << endl;
    if (bhtree.body) {
        s << *(bhtree.body) << endl << endl;
    } else {
        s << "No Body" << endl << endl;
    }

    if (bhtree.ne) {
        s << "NE: " << *bhtree.ne << endl;
    }
    if (bhtree.nw) {
        s << "NW: " << *bhtree.nw << endl;
    }
    if (bhtree.se) {
        s << "SE: " << *bhtree.se << endl;
    }
    if (bhtree.sw) {
        s << "SW: " << *bhtree.sw << endl;
    }
    return s;
}
