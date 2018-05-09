#include "quadtree.h"

quadtree::quadtree(ofRectangle b, int n) {
    boundary = b;
    capacity = n;
    isDivided = false;
}

void quadtree::init(ofRectangle b, int n) {
    boundary = b;
    capacity = n;
    isDivided = false;
}

void quadtree::insert(boid *b) {
    
    if (!boundary.inside(b->position.x, b->position.y)) {
        return;
    }
    
    if (points.size() < capacity) {
        points.push_back(b);
    } else {
        if (!isDivided) {
            subdivide();
        }
        nw->insert(b);
        ne->insert(b);
        se->insert(b);
        sw->insert(b);
    }
    
}

void quadtree::subdivide() {
    nw = new quadtree(ofRectangle(boundary.x                     , boundary.y                      , boundary.width / 2, boundary.height / 2), capacity);
    ne = new quadtree(ofRectangle(boundary.x + boundary.width / 2, boundary.y                      , boundary.width / 2, boundary.height / 2), capacity);
    se = new quadtree(ofRectangle(boundary.x + boundary.width / 2, boundary.y + boundary.height / 2, boundary.width / 2, boundary.height / 2), capacity);
    sw = new quadtree(ofRectangle(boundary.x                     , boundary.y + boundary.height / 2, boundary.width / 2, boundary.height / 2), capacity);
    isDivided = true;
}

vector<boid*> quadtree::query(ofRectangle range) {
    vector<boid*> found;
    
    if (!boundary.intersects(range)) {
        return found;
    } else {
        for (int i = 0; i < points.size(); i++) {
            if (range.inside(points[i]->position.x, points[i]->position.y)) {
                found.push_back(points[i]);
            }
        }
        
        if (isDivided) {
            vector<boid*> nwq = nw->query(range);
            vector<boid*> neq = ne->query(range);
            vector<boid*> seq = se->query(range);
            vector<boid*> swq = sw->query(range);
            found.insert(found.end(), nwq.begin(), nwq.end());
            found.insert(found.end(), neq.begin(), neq.end());
            found.insert(found.end(), seq.begin(), seq.end());
            found.insert(found.end(), swq.begin(), swq.end());
        }
        return found;
    }
}
