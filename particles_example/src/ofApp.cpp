#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0);
    
    int countParticles = 10;
    for (int i = 0; i < countParticles; i++) {
        ParticleVec3 tmp;
        tmp.position = ofVec3f(ofRandomWidth(), ofRandomHeight(), 0);
        tmp.velocity = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), 0);
        tmp.radius = ofRandom(20, 50);
        particles.push_back(tmp);
    }
}

//--------------------------------------------------------------
void ofApp::update(){

    for (int i = 0; i < particles.size(); i++) {
        particles[i].addForce(0.01 * particles[i].velocity.getNormalized());
        particles[i].bounceOffWalls();
        particles[i].update();
        for (int j = i + 1; j < particles.size(); j++) {
            float distance = particles[i].position.distance(particles[j].position);
            float minDistance = particles[i].radius + particles[j].radius;
            if (distance < minDistance) {
                ofVec3f pDiff = particles[i].position - particles[j].position;
                ofVec3f vDiff = particles[i].velocity - particles[j].velocity;
                ofVec3f iNewVel = particles[i].velocity - (vDiff.dot(pDiff) / pDiff.lengthSquared()) * pDiff;
                ofVec3f jNewVel = particles[j].velocity - (-vDiff.dot(-pDiff) / pDiff.lengthSquared()) * -pDiff;
                particles[i].velocity = iNewVel;
                particles[j].velocity = jNewVel;
            }
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofNoFill();
    for (int i = 0; i < particles.size(); i++) {
        particles[i].draw();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
