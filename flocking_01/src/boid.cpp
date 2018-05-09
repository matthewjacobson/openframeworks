#include "boid.h"

boid::boid(float x, float y) {
    
    acceleration = ofVec3f(0, 0, 0);
    
    float angle = ofRandom(0, 2 * PI);
    velocity = ofVec3f(cos(angle), sin(angle));
    
    position = ofVec3f(x, y, 0);
    
    r = ofRandom(1, 3);
    maxspeed = ofRandom(1, 3);
    maxforce = 0.03;
    
    mass = 1;
    
    trail.setMode(OF_PRIMITIVE_LINE_STRIP);
    
}

void boid::run(vector<boid*> boids) {
    flock(boids);
    update();
    borders();
}

void boid::applyForce(ofVec3f force) {
    acceleration += force;
}

void boid::flock(vector<boid*> boids) {
    
    ofVec3f sep = separate(boids);   // Separation
    ofVec3f ali = align(boids);      // Alignment
    ofVec3f coh = cohesion(boids);   // Cohesion
    
    // Arbitrarily weight these forces
//    sep *= 3.5;
//    ali *= 1.0;
//    coh *= 0.5;
    ofSeedRandom(0);
    sep *= 0.2 * sin(ofRandom(0.1, 0.5) * ofGetElapsedTimef() + ofRandom(0, 2 * PI)) + 0.5;
    ali *= 0.2 * sin(ofRandom(0.1, 0.5) * ofGetElapsedTimef() + ofRandom(0, 2 * PI)) + 0.2;
    coh *= 0.2 * sin(ofRandom(0.1, 0.5) * ofGetElapsedTimef() + ofRandom(0, 2 * PI)) + 0.2;
    
    // Add the force vectors to acceleration
    applyForce(sep);
    applyForce(ali);
    applyForce(coh);
    
}

void boid::update() {
    // Update velocity
    velocity += acceleration;
    // Limit speed
    if (velocity.length() > maxspeed) {
        velocity.normalize();
        velocity *= maxspeed;
    }
    position += velocity;
    // Reset accelertion to 0 each cycle
    acceleration *= 0;
    
}

ofVec3f boid::seek(ofVec3f target) {
    ofVec3f desired = target - position;

    desired.normalize();
    desired *= maxspeed;
    
    ofVec3f steer = desired - velocity;
    if (steer.length() > maxforce) {
        steer.normalize();
        steer *= maxforce;
    }
    
    return steer;
}

void boid::borders() {
    if (position.x < -r) {
        position.x = ofGetWidth() + r;
        trail.clear();
    }
    if (position.y < -r) {
        position.y = ofGetHeight() + r;
        trail.clear();
    }
    if (position.x > ofGetWidth() + r) {
        position.x = -r;
        trail.clear();
    }
    if (position.y > ofGetHeight() + r) {
        position.y = -r;
        trail.clear();
    }
}

ofVec3f boid::separate(vector<boid*> boids) {
    float desiredseparation = 25.0f;
    ofVec3f steer = ofVec3f(0, 0, 0);
    int count = 0;
    // For every boid in the system, check if it's too close
    for (boid* other : boids) {
        float d = position.distance(other->position);
        // If the distance is greater than 0 and less than an arbitrary amount (0 when you are yourself)
        if ((d > 0) && (d < desiredseparation)) {
            // Calculate vector pointing away from neighbor
            ofVec3f diff = position - other->position;
            diff.normalize();
            diff /= d;        // Weight by distance
            steer += diff;
            count++;            // Keep track of how many
        }
    }
    
    if (count > 0) {
        steer /= (float)count;
    }
    
    if (steer.length() > 0) {
        steer.normalize();
        steer *= maxspeed;
        steer -= velocity;
        if (steer.length() > maxforce) {
            steer.normalize();
            steer *= maxforce;
        }
    }
    
    return steer;
}

ofVec3f boid::align(vector<boid*> boids) {
    float neighbordist = 50;
    ofVec3f sum = ofVec3f(0, 0, 0);
    int count = 0;
    for (boid* other : boids) {
        float d = position.distance(other->position);
        if ((d > 0) && (d < neighbordist)) {
            sum += other->velocity;
            count++;
        }
    }
    if (count > 0) {
        sum /= (float)count;
        sum.normalize();
        sum *= maxspeed;
        ofVec3f steer = sum - velocity;
        if (steer.length() > maxforce) {
            steer.normalize();
            steer *= maxforce;
        }
        return steer;
    }
    else {
        return ofVec3f(0, 0, 0);
    }
}

ofVec3f boid::cohesion(vector<boid*> boids) {
    float neighbordist = 50;
    ofVec3f sum = ofVec3f(0, 0, 0);   // Start with empty vector to accumulate all positions
    int count = 0;
    for (boid* other : boids) {
        float d = position.distance(other->position);
        if ((d > 0) && (d < neighbordist)) {
            sum += other->position; // Add position
            count++;
        }
    }
    if (count > 0) {
        sum /= count;
        return seek(sum);  // Steer towards the position
    }
    else {
        return ofVec3f(0, 0, 0);
    }
}
















