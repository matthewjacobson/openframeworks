#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0);
    
    float w = 500;
    float h = 500;
    float cw = 20;
    float ch = 20;
    for (int i = 0; i <= cw; i++) {
        float x = ofMap(i, 0, cw, -w / 2, w / 2);
        for (int j = 0; j <= ch; j++) {
            
            int thisIndex = particles.size();
            float y = ofMap(j, 0, ch, -h / 2, h / 2);
            
            ParticleVec3 tmp;
            tmp.position = ofVec3f(x, y, 0);
            particles.push_back(tmp);
            
            if (i != cw) {
                Edge right;
                right.p1 = thisIndex;
                right.p2 = thisIndex + ch + 1;
                edges.push_back(right);
            }
            if (j != ch) {
                Edge down;
                down.p1 = thisIndex;
                down.p2 = thisIndex + 1;
                edges.push_back(down);
            }
            if (i != cw && j != ch) {
                Edge downRight;
                downRight.p1 = thisIndex;
                downRight.p2 = thisIndex + ch + 2;
                edges.push_back(downRight);
            }
            
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){

    float w = ofGetWidth();
    float h = ofGetHeight();
    
    for (int i = 0; i < edges.size(); i++) {
        ParticleVec3 p1 = particles[edges[i].p1];
        ParticleVec3 p2 = particles[edges[i].p2];
        ofVec3f f = (p1.position - p2.position).normalize();
        f *= -0.01 * (p1.position.distance(p2.position) - 40);
        f -= 0.9 * (p1.velocity - p2.velocity).normalize();
        particles[edges[i].p1].addForce(f);
        particles[edges[i].p2].addForce(-f);
        
    }
    
    for (int i = 0; i < particles.size(); i++) {
        
        for (int j = 0; j < particles.size(); j++) {
            if (i != j) particles[i].addRepulsionForce(particles[j], 20, 50);
        }
        particles[i].update();
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

    for (ParticleVec3 p : particles) {
        p.draw();
    }
    
//    for (Edge e : edges) {
//        ofDrawLine(particles[e.p1].position.x, particles[e.p1].position.y, particles[e.p2].position.x, particles[e.p2].position.y);
//    }
    
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
