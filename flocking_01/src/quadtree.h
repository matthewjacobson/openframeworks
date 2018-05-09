#pragma once

#include "ofMain.h"
#include "boid.h"
#include "quadtree.h"

class quadtree {
    
public:
    
    quadtree(ofRectangle b, int n);
    void init(ofRectangle b, int n);
    void insert(boid *b);
    void subdivide();
    vector<boid*> query(ofRectangle range);
    
    ofRectangle boundary;
    int capacity;
    vector<boid*> points;
    quadtree *nw, *ne, *se, *sw;
    bool isDivided;
    
};
