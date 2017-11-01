#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    str = "OKAYO";
//    myFont.load("BEBAS.ttf", 100, true, true, true);
    myFont.load("CaviarDreams.ttf", 100, true, true, true);
//    myFont.load("keifont.ttf", 100, true, true, true);
    chars = myFont.getStringAsPoints(str);
    
    ofBackground(0);
    
    ofHideCursor();
    
    countLevels = 30;
}

//--------------------------------------------------------------
void ofApp::update(){
    myFont.setLetterSpacing(1);
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofTranslate(mouseX, mouseY);
    float y = 0;
    ofRectangle b = myFont.getStringBoundingBox(str, 0, 0);
    for (int i = 0; i < countLevels; i++) {
        float w = b.width / (i + 1);
        float h = b.height / (i + 1);
        for (int j = 0; j < i + 1; j++) {
            float s = MAX(1 / float(i + 1), 0.025);
            ofSetColor(255, ofMap(i, 0, countLevels, 255, 0));
            ofPushMatrix();
                ofTranslate(ofGetWidth() / 2, b.height / 2);
                ofTranslate(w / 2 - b.width / 2, h / 2 - b.height / 2);
                ofTranslate(j * w, 0);
                ofTranslate(0, y);
                ofScale(s, s); // scaling
                ofTranslate(-b.width / 2, -b.height / 2); // translate to center of bounding box
                myFont.drawString(str, -b.x, -b.y); // draw string in top left
            ofPopMatrix();
        }
        y += h;
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
