#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    string text = "this is a test";

    p.setText(text);
    p.setColor(ofColor(0));
    p.setAlignment(ofxParagraph::ALIGN_CENTER);
    
    int pWidth = 340;
    int pFontSize = 14;
    float pPadding = pWidth*.30;
    
    p.setFont(ofxSmartFont::add("raleway/Raleway-Medium.ttf", pFontSize, "raleway-medium"));
    
    int pLeading = pFontSize*.65;
    
    p.setWidth(pWidth);
    p.setLeading(pLeading);
    p.setSpacing(pFontSize*.7);
    p.setBorderPadding(30);
}

//--------------------------------------------------------------
void ofApp::update(){

    p.setPosition(mouseX, mouseY);
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    p.draw();
    
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
