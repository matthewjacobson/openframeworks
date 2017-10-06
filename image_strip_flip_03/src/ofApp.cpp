#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    freeze = false;
    
    camWidth = ofGetWidth();
    camHeight = ofGetHeight();
    myVideoGrabber.initGrabber(camWidth, camHeight);
    myTexture.allocate(camWidth, camHeight, GL_RGB);
}

//--------------------------------------------------------------
void ofApp::update(){
    myVideoGrabber.update();
    if(myVideoGrabber.isFrameNew()){
        ofPixels pixelData = myVideoGrabber.getPixels();
        myTexture.allocate(pixelData);
        myTexture.bind();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    ofSeedRandom(0);
    
    if (!freeze) {
        countStripsX = floor(10 * ofNoise(100, 100, 0.05 * ofGetElapsedTimef())) + 4;
        countStripsY = floor(10 * ofNoise(300, 150, 0.05 * ofGetElapsedTimef())) + 2;
    }
    
    int res = 500;
    for (int i = 0; i < countStripsX; i++) {
        float x1 = ofMap(i, 0, countStripsX, 0, ofGetWidth());
        float x2 = ofMap(i + 1, 0, countStripsX, 0, ofGetWidth());
        for (int j = 0; j < countStripsY; j++) {
            float y1 = ofMap(j, 0, countStripsY, 0, ofGetHeight());
            float y2 = ofMap(j + 1, 0, countStripsY, 0, ofGetHeight());
            
            float rand = ofRandom(1);
            glBegin(GL_QUAD_STRIP);
            for (int k = 0; k < res; k++) {
                if (rand < 0.5) {
                    float x = ofMap(k, 0, res, x1, x2);
                    float t = ofMap(k, 0, res, 0, PI / 3) + 6 * ofSignedNoise(x1, y1, 0.1 * ofGetElapsedTimef()) + 100;
                    float wave = MIN(MAX(2 * cos(t), -1), 1);
                    glVertex2f(x, (y1 + y2) / 2 - (y2 - y1) / 2 * wave);
                    if (fmod(t, 2 * PI) < PI / 2 || fmod(t, 2 * PI) > 3 * PI / 2) glTexCoord2f(x, (y1 + y2) / 2 - (y2 - y1) / 2 * wave);
                    else glTexCoord2f(x, (y1 + y2) / 2 + (y2 - y1) / 2 * wave);
                    glVertex2f(x, (y1 + y2) / 2 + (y2 - y1) / 2 * wave);
                    if (fmod(t, 2 * PI) < PI / 2 || fmod(t, 2 * PI) > 3 * PI / 2) glTexCoord2f(x, (y1 + y2) / 2 + (y2 - y1) / 2 * wave);
                    else glTexCoord2f(x, (y1 + y2) / 2 - (y2 - y1) / 2 * wave);
                }
                else {
                    float y = ofMap(k, 0, res, y1, y2);
                    float t = ofMap(k, 0, res, 0, PI / 3) + 6 * ofSignedNoise(x1, y1, 0.1 * ofGetElapsedTimef());
                    float wave = MIN(MAX(2 * cos(t), -1), 1);
                    glVertex2f((x1 + x2) / 2 - (x2 - x1) / 2 * wave, y);
                    if (fmod(t, 2 * PI) < PI / 2 || fmod(t, 2 * PI) > 3 * PI / 2) glTexCoord2f((x1 + x2) / 2 - (x2 - x1) / 2 * wave, y);
                    else glTexCoord2f((x1 + x2) / 2 + (x2 - x1) / 2 * wave, y);
                    glVertex2f((x1 + x2) / 2 + (x2 - x1) / 2 * wave, y);
                    if (fmod(t, 2 * PI) < PI / 2 || fmod(t, 2 * PI) > 3 * PI / 2) glTexCoord2f((x1 + x2) / 2 + (x2 - x1) / 2 * wave, y);
                    else glTexCoord2f((x1 + x2) / 2 - (x2 - x1) / 2 * wave, y);
                }
            }
            glEnd();
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') freeze = !freeze;
    if (key == OF_KEY_UP) countStripsX++;
    if (key == OF_KEY_DOWN) countStripsX--;
    if (key == OF_KEY_RIGHT) countStripsY++;
    if (key == OF_KEY_LEFT) countStripsY--;
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
