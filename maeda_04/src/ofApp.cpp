#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    str = "whatever";
    countCopies = 100;
    
    myFont.setSpaceSize(5);
    myFont.load("BEBAS.ttf", 100, true, true, true);
    vector<ofTTFCharacter> chars = myFont.getStringAsPoints(str);
    bound = myFont.getStringBoundingBox(str, 0, 0);
    
    for (int i = 0; i < chars.size(); i++) {
        letter l;
        vector<vector<ofPoint>> tempPoints;
        for (int j = 0; j < chars[i].getOutline().size(); j++) {
            vector<ofPoint> outline = chars[i].getOutline()[j].getResampledBySpacing(2).getVertices();
            for (int k = 0; k < outline.size(); k++) {
                outline[k] -= ofPoint(bound.x + bound.width / 2, bound.y + bound.height / 2);
            }
            tempPoints.push_back(outline);
        }
        l.setup(tempPoints);
        word.push_back(l);
    }
    cout << word[1].center << endl;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    ofTranslate(ofGetWidth() / 2, bound.height / 2);
    
    ofSeedRandom(0);
    
    for (float j = 0; j < word.size(); j++) {
        letter l = word[j];
//        for (float i = 0; i < countCopies; i++) {
        for (float i = countCopies - 1; i >= 0; i--) {
            if (i == 0) {
                ofSetColor(150, 0, 0, 255);
                ofFill();
            }
            else {
                ofNoFill();
                ofSetColor(150, 0, 0, ofMap(i, 0, countCopies, 200, 0));
                ofSetLineWidth(2);
            }
            ofPushMatrix();
                ofTranslate(0, ofMap(i, 0, countCopies, 0, ofGetHeight()));
                ofTranslate(l.center);
//                ofRotateY(ofMap(i, 0, countCopies, 0, 1) * 360 * ofNoise(i / 30, j, ofGetElapsedTimef()));
                ofRotateZ(ofMap(i, 0, countCopies, 0, 1) * 200 * ofNoise(i / 30 + 100, 20 * j + 200, 0.2 * ofGetElapsedTimef()));
                ofRotateY(ofMap(i, 0, countCopies, 0, 1) * 500);
                ofRotateX(ofMap(i, 0, countCopies, 0, 1) * 500 * ofNoise(i / 30, 20 * j, 0.5 * ofGetElapsedTimef()));
                ofScale(ofMap(i, 0, countCopies, 1, 0), ofMap(i, 0, countCopies, 1, 0));
                ofTranslate(-l.center);
                l.draw();
            ofPopMatrix();
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
