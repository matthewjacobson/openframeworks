#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0);
    
    // MESS WITH THESE PARAMETERS //
    minBlobRadius = 100;
    maxBlobRadius = 200;
    noiseAmplitude = 5;
    noiseFrequency = 1;
    // MESS WITH THESE PARAMETERS //
    
    sphere = ofMesh::icosphere(1, 4);
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    blob = sphere;
    
    for (int i = 0; i < blob.getVertices().size(); i++) {
        ofVec3f originalPosition = blob.getVertices()[i];
        float positionNoise = noiseAmplitude * ofNoise(noiseFrequency * originalPosition);
        ofVec3f newPosition = originalPosition * ofMap(sin(positionNoise + ofGetElapsedTimef()), -1, 1, minBlobRadius, maxBlobRadius);
        blob.setVertex(i, newPosition);
    }
    
    ofxMeshUtils::calcNormals(blob, true);
    
    for (int i = 0; i < blob.getVertices().size(); i++) {
        ofVec3f v = blob.getVertices()[i];
        ofVec3f n = blob.getNormals()[i];
        ofVec3f l = ofVec3f(0, 2000, 0);
        float shade = ofMap(acos(n.dot((l - v).normalize())), 0, PI, 255, 0);
        blob.addColor(ofColor(shade));
    }
    
    ofEnableDepthTest();
    blob.draw();
    ofDisableDepthTest();
    
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
