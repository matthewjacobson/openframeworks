#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    font.load("BEBAS.ttf", 200, true, true, true);
    
    saveFrame = false;
//    ofNoFill();
//    ofSetColor(0);
    frameCount = 0;
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    vector<ofPoint> points = font.getCharacterAsPoints('A').getOutline()[0].getResampledBySpacing(2).getVertices();
    ofRectangle boundingBox = font.getStringBoundingBox("A", 0, 0);
    
    svgWidth = ofGetWidth();
    svgHeight = ofGetHeight();
    
    if (saveFrame) {
        frameCount++;
        svgWidth = 2550;
        svgHeight = 3300;
        ofBeginSaveScreenAsSVG("out" + ofToString(frameCount) + ".svg", false, true, ofRectangle(0, 0, svgWidth, svgHeight));
    }
    
    ofTranslate(svgWidth / 2, svgHeight / 2);
    
    int countCopies = 20;
//    for (int n = 0; n < countCopies; n++) {
    for (int n = countCopies - 1; n >= 0; n--) {
        if (n % 2 == 0) ofSetColor(0);
        else ofSetColor(255);
        ofBeginShape();
            for (int i = 0; i < points.size(); i++) {
                ofVec3f p = points[i];
                ofVec3f adj = ofVec2f(boundingBox.x + boundingBox.width / 2, boundingBox.y + boundingBox.height / 2);
                float noise = ofMap(n, 0, countCopies, 1, 30) * (ofMap(n, 0, countCopies, 0, 1) * ofNoise(0.01 * (p - adj + ofVec3f(mouseX, mouseY, 0))) + 0.25);
                ofVec3f out = noise * (p - adj);
                ofVertex(out);
            }
        ofEndShape(OF_CLOSE);
    }
    
    if (saveFrame) {
        ofEndSaveScreenAsSVG();
        saveFrame = false;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        saveFrame = true;
    }
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
