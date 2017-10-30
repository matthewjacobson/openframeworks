#include "ofApp.h"

ofPoint getIntersection(ofPoint _s, ofPoint _e, vector<ofTTFCharacter> _c) {
    ofPoint out;
    float minDist = 100000;
    for (ofTTFCharacter c : _c) {
        vector<ofPolyline> o = c.getOutline();
        for (ofPolyline l : o) {
            vector<ofPoint> p = l.getResampledBySpacing(20).getVertices();
            for (int i = 0; i < p.size(); i++) {
                ofPoint sTest = p[i];
                ofPoint eTest = p[(i + 1) % p.size()];
                ofPoint temp;
                Boolean checkIntersect = ofLineSegmentIntersection(_s, _e, sTest, eTest, temp);
                if (checkIntersect && _s.distance(temp) < minDist && _s.distance(temp) > 10) {
                    minDist = _s.distance(temp);
                    out = temp;
                }
            }
        }
    }
    if (minDist != 100000) return out;
    else return _e;
}

void drawGradientLine(ofPoint _s, ofPoint _e, int _n) {
    ofPolyline t1;
    t1.addVertices({_s, _e});
    ofMesh t2;
    t2.setMode(OF_PRIMITIVE_LINE_STRIP);
    for (int i = 0; i < t1.getResampledBySpacing(20).getVertices().size(); i++) {
        float d = t1.getResampledBySpacing(20).getVertices()[i].distance(_e) / _s.distance(_e);
        t2.addVertex(t1.getResampledBySpacing(20).getVertices()[i]);
        t2.addColor(ofFloatColor(MIN(ofMap(pow(d, 2), 0, 1, 0, 255), 255),255));
//        t2.addColor(ofFloatColor(ofMap(pow(d, 5), 0, 1, 0, 50), ofMap(pow(d, 5), 0, 1, 0, 100), ofMap(pow(d, 5), 0, 1, 0, 255), 50));
    }
    t2.draw();
}

//--------------------------------------------------------------
void ofApp::setup(){
    str = "what?";
    ofBackground(0);
    myFont.load("BEBAS.ttf", 250, true, true, true);
//    myFont.load("CaviarDreams.ttf", 250, true, true, true);
    chars = myFont.getStringAsPoints(str);
    countFrames = 50;
}

//--------------------------------------------------------------
void ofApp::update(){
//    myFont.setSpaceSize(mouseX);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    if (ofGetFrameNum() % (2 * countFrames) < countFrames) {
        str = "what";
        chars = myFont.getStringAsPoints(str);
    }
    else {
        str = "ever";
        chars = myFont.getStringAsPoints(str);
    }
    
    ofRectangle b = myFont.getStringBoundingBox(str, 0, 0);
    ofTranslate(-(b.x + b.width / 2), -(b.y + b.height / 2));
    
    for (ofTTFCharacter c : chars) {
        vector<ofPolyline> outlines = c.getOutline();
        for (ofPolyline p : outlines) {
            vector<ofPoint> points = p.getResampledBySpacing(10).getVertices();
            for (int i = 0; i < points.size(); i++) {
                ofPoint v = points[i];
                ofPoint intersect = getIntersection(v, v + ofPoint(
                           100 * cos(1 * ofGetElapsedTimef() + ofMap(i, 0, points.size(), 0, 2 * PI / 100) - 2 * PI * ofNoise(0.1 * ofGetElapsedTimef())),
                           100 * sin(1 * ofGetElapsedTimef() + ofMap(i, 0, points.size(), 0, 2 * PI / 100) - 2 * PI * ofNoise(0.1 * ofGetElapsedTimef()))), chars);
//                ofPoint intersect = getIntersection(v, v + ofPoint(mouseX, mouseY), chars);
                drawGradientLine(v, intersect, 1);
            }
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == OF_KEY_LEFT) countFrames--;
    if (key == OF_KEY_RIGHT) countFrames++;
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
