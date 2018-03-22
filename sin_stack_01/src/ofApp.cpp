#include "ofApp.h"

float ofApp::sumSin(vector<sinusoid> s, float x) {
    float sum = 0;
    for (int i = 0; i < s.size(); i++) {
        sum += getSin(s[i], x);
    }
    return sum;
}

float ofApp::getSin(sinusoid s, float x) {
    return s.a * sin(s.f * 2 * PI * s.t * x + s.p) + 2 * s.a;
}

//--------------------------------------------------------------
void ofApp::setup(){

    countLayers = 20;
    
    for (int i = 0; i < countLayers; i++) {
        sinusoid s;
        s.a = ofRandom(1, 1);
        s.f = ofRandom(0, 5);
        s.p = ofRandom(0, 2 * PI);
        s.t = ofRandom(0.5, 2);
        sinusoids.push_back(s);
    }
    
    ofBackground(0);
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    ofSetColor(255);
    
    for (float x = -0.5 * ofGetWidth(); x < 0.5 * ofGetWidth(); x += 2) {
        float r = -0.5;
        ofDrawCircle(x, -ofGetHeight() / 2, 5);
        for (int i = 0; i < countLayers; i++) {
            r += getSin(sinusoids[i], x / 500 + 0.2 * ofGetElapsedTimef()) / sumSin(sinusoids, x / 500 + 0.2 * ofGetElapsedTimef());
            float y = ofMap(r, -0.5, 0.5, -ofGetHeight() / 2, ofGetHeight() / 2);
            ofDrawCircle(x, y, 1);
        }
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
