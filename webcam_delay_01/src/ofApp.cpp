#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    countFrames = 5;
    pause = false;
    
    cam.setup(640, 480);
    
    for (int i = 0; i < countFrames; i++) {
        
        ofImage tmp;
        tmp.allocate(cam.getWidth(), cam.getHeight(), OF_IMAGE_COLOR);
        sequence.push_back(tmp);
        
    }
    
    current.allocate(cam.getWidth(), cam.getHeight(), GL_RGBA);
    past.allocate(cam.getWidth(), cam.getHeight(), GL_RGBA);
    
}

//--------------------------------------------------------------
void ofApp::update(){

    cam.update();
    
    if (cam.isFrameNew()) {
        
        ofImage tmp;
        tmp.setFromPixels(cam.getPixels());

        sequence.erase(sequence.begin());
        sequence.push_back(tmp);
        
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    current.begin();
        sequence[countFrames - 1].draw(0, 0);
    current.end();
    if (!pause) {
        past.begin();
            sequence[0].draw(0, 0);
        past.end();
    }
    
    
    int cw = 64;
    int ch = 48;
    float w = ofGetWidth() / cw;
    float h = ofGetHeight() / ch;
    for (int i = 0; i < cw; i++) {
        for (int j = 0; j < ch; j++) {

            float tlx = ofMap(i, 0, cw, 0, ofGetWidth());
            float tly = ofMap(j, 0, ch, 0, ofGetHeight());
            
            if ((i + j) % 2 == 0) {
                current.getTexture().drawSubsection(tlx, tly, w, h, tlx, tly, w, h);
            } else {
                past.getTexture().drawSubsection(tlx, tly, w, h, tlx, tly, w, h);
            }

        }
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == ' ') {
        pause = !pause;
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
