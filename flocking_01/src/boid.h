#pragma once

#include "ofMain.h"

class boid {
    
public:
    
    boid(float x, float y);
    void run(vector<boid*> boids);
    void applyForce(ofVec3f force);
    void flock(vector<boid*> boids);
    void update();
    ofVec3f seek(ofVec3f target);
    void borders();
    ofVec3f separate(vector<boid*> boids);
    ofVec3f align(vector<boid*> boids);
    ofVec3f cohesion(vector<boid*> boids);
    
    ofVec3f position;
    ofVec3f velocity;
    ofVec3f acceleration;
    float mass;
    float r;
    float maxforce;
    float maxspeed;
    ofMesh trail;
    
};
