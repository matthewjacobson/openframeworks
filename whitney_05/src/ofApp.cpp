#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    countLevels = 100;
//    rotationSpeed = 5;
    
    texture.load("image.png");
    
    gui.setup();
    gui.add(framePad.setup("framePad", 2, 0.75, 2));
    gui.add(imageSize.setup("imageSize", 50, 25, 200));
    gui.add(countLevels.setup("countLevels", 80, 25, 200));
    gui.add(rotationSpeed.setup("rotationSpeed", 1, 0, 10));
    gui.add(spiral.setup("spiral", false));
}

//--------------------------------------------------------------
void ofApp::update(){
    texture.resize(imageSize, imageSize);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    
    gui.draw();
    
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    float spiralRadius;
    if (spiral) spiralRadius = 50;
    else spiralRadius = 0;
    for (int n = 1; n < countLevels; n++) {
        for (int i = 0; i < n; i++) {
            float r = framePad * MIN(ofGetWidth() / 2, ofGetHeight() / 2) * n / countLevels;
            float t = ofMap(i, 0, n, 0, 2 * PI) + rotationSpeed * n / countLevels * (ofGetElapsedTimef() + ofSignedNoise(n / countLevels, 0.5 * ofGetElapsedTimef(), 0.1 * ofGetElapsedTimef()));
            float x = r * cos(t) + (1 - n / countLevels) * spiralRadius * sin(ofGetElapsedTimef() + 5 * PI * n / countLevels);
            float y = r * sin(t) + (1 - n / countLevels) * spiralRadius * cos(ofGetElapsedTimef() + 5 * PI * n / countLevels);
            ofSetColor(127 + 0.01 * (n * i), 127 + 0.02 * (n * i), 127 + 0.9 * (n * i), 255);
            ofDrawCircle(x, y, 1);
            texture.draw(x - texture.getWidth() / 2, y - texture.getHeight() / 2);
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
