#include "ofApp.h"

Boolean myCompare(ofPoint _a, ofPoint _b) {
    return _a.x < _b.x;
}

//--------------------------------------------------------------
void ofApp::setup(){
    
    framePad = 0.95;
    countBoxes = 6;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(255);
    ofSetColor(0);
    
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    ofNoFill();
    
    ofSeedRandom(0);
    
    float screenSideLength = MIN(ofGetWidth(), ofGetHeight());
    float sideLength = framePad * screenSideLength / countBoxes;
    
    for (int i = 0; i < countBoxes; i++) {
        for (int j = 0; j < countBoxes; j++) {
            float cx = ofMap(i, 0, countBoxes, -framePad * screenSideLength / 2, framePad * screenSideLength / 2) + sideLength / 2;
            float cy = ofMap(j, 0, countBoxes, -framePad * screenSideLength / 2, framePad * screenSideLength / 2) + sideLength / 2;
            
//            addFullBoxPath(cx, cy, sideLength);
//            addHalfRectPath(cx, cy, sideLength, floor(ofRandom(0, 4)));
//            addHalfTriPath(cx, cy, sideLength, floor(ofRandom(0, 4)));
//            addQtrTriPath1(cx, cy, sideLength, floor(ofRandom(0, 4)));
//            addQtrTriPath2(cx, cy, sideLength, floor(ofRandom(0, 4)));
            
            float rand1 = ofRandom(0, 1);
            if (rand1 < .2) addFullBoxPath(cx, cy, sideLength);
            else if (rand1 < .4) addHalfRectPath(cx, cy, sideLength, floor(ofRandom(0, 4)));
            else if (rand1 < .6) addHalfTriPath(cx, cy, sideLength, floor(ofRandom(0, 4)));
            else if (rand1 < .8) addQtrTriPath1(cx, cy, sideLength, floor(ofRandom(0, 4)));
            else addQtrTriPath2(cx, cy, sideLength, floor(ofRandom(0, 4)));
            
            float rand2 = ofRandom(0, 1);
            if (rand2 < .2) addFullBoxPath(cx, cy, sideLength);
            else if (rand2 < .4) addHalfRectPath(cx, cy, sideLength, floor(ofRandom(0, 4)));
            else if (rand2 < .6) addHalfTriPath(cx, cy, sideLength, floor(ofRandom(0, 4)));
            else if (rand2 < .8) addQtrTriPath1(cx, cy, sideLength, floor(ofRandom(0, 4)));
            else addQtrTriPath2(cx, cy, sideLength, floor(ofRandom(0, 4)));
            
        }
    }
    
    for (int i = 0; i < grid.getOutline().size(); i++) {
        ofPolyline box = grid.getOutline()[i];
        //box.draw();
        float spacing = ofMap(ofNoise(box.getCentroid2D().x, box.getCentroid2D().y, 100), 0, 1, 2, 20);
        float rotation = 180 * ofNoise(box.getCentroid2D().x, box.getCentroid2D().y);
        ofPath lineFill = getLineFill(box, spacing, rotation);
        for (int j = 0; j < lineFill.getOutline().size(); j++) {
            ofPolyline line = lineFill.getOutline()[j];
            line.draw();
        }
    }
    
    ofSaveScreen("test.png");
}

ofPath ofApp::getLineFill(ofPolyline _p, float _s, float _t) {
    ofPath result;
    
    vector<ofPoint> v = _p.getVertices();
    ofPoint c = _p.getCentroid2D();
    
    float xMin, xMax, yMin, yMax;
    for (int i = 0; i < v.size(); i++) {
        v[i] -= c;
        v[i].rotate(_t, ofVec3f(0, 0, 1));
        (i == 0)?(xMin = v[i].x):(xMin = MIN(xMin, v[i].x));
        (i == 0)?(xMax = v[i].x):(xMax = MAX(xMax, v[i].x));
        (i == 0)?(yMin = v[i].y):(yMin = MIN(yMin, v[i].y));
        (i == 0)?(yMax = v[i].y):(yMax = MAX(yMax, v[i].y));
    }
    
    for (float y = yMin; y < yMax; y += _s) {
        vector<ofPoint> intersections;
        for (int i = 0; i < v.size(); i++) {
            ofPoint s = v[i];
            ofPoint e = v[(i + 1) % v.size()];
            ofPoint intersection;
            Boolean checkIntersect = ofLineSegmentIntersection(s, e, ofPoint(xMin, y), ofPoint(xMax, y), intersection);
            if (checkIntersect) intersections.push_back(intersection);
        }
        ofSort(intersections, myCompare);
        for (int i = 0; i < intersections.size(); i += 2) {
            ofPoint p1 = intersections[i];
            ofPoint p2 = intersections[(i + 1) % intersections.size()];
            result.moveTo(p1.x, p1.y);
            result.lineTo(p2.x, p2.y);
            result.close();
        }
    }
    
    result.rotate(-_t, ofVec3f(0, 0, 1));
    result.translate(c);
    
    return result;
}

void ofApp::addFullBoxPath(float _x, float _y, float _s) {
    float halfSide = _s / 2;
    grid.moveTo(_x - _s / 2, _y - _s / 2);
    grid.lineTo(_x + _s / 2, _y - _s / 2);
    grid.lineTo(_x + _s / 2, _y + _s / 2);
    grid.lineTo(_x - _s / 2, _y + _s / 2);
    grid.close();
}
void ofApp::addHalfRectPath(float _x, float _y, float _s, int _d) {
    float halfSide = _s / 2;
    float rotateDeg = 90 * _d;
    ofPoint a = ofPoint(-halfSide, -halfSide).rotate(0, 0, rotateDeg) + ofPoint(_x, _y);
    ofPoint b = ofPoint(halfSide, -halfSide).rotate(0, 0, rotateDeg) + ofPoint(_x, _y);
    ofPoint c = ofPoint(halfSide, 0).rotate(0, 0, rotateDeg) + ofPoint(_x, _y);
    ofPoint d = ofPoint(-halfSide, 0).rotate(0, 0, rotateDeg) + ofPoint(_x, _y);
    grid.moveTo(a.x, a.y);
    grid.lineTo(b.x, b.y);
    grid.lineTo(c.x, c.y);
    grid.lineTo(d.x, d.y);
    grid.close();
}
void ofApp::addHalfTriPath(float _x, float _y, float _s, int _d) {
    float halfSide = _s / 2;
    float rotateDeg = 90 * _d;
    ofPoint a = ofPoint(-halfSide, halfSide).rotate(0, 0, rotateDeg) + ofPoint(_x, _y);
    ofPoint b = ofPoint(-halfSide, -halfSide).rotate(0, 0, rotateDeg) + ofPoint(_x, _y);
    ofPoint c = ofPoint(halfSide, -halfSide).rotate(0, 0, rotateDeg) + ofPoint(_x, _y);
    grid.moveTo(a.x, a.y);
    grid.lineTo(b.x, b.y);
    grid.lineTo(c.x, c.y);
    grid.close();
}
void ofApp::addQtrTriPath1(float _x, float _y, float _s, int _d) {
    float halfSide = _s / 2;
    float rotateDeg = 90 * _d;
    ofPoint a = ofPoint(-halfSide, -halfSide).rotate(0, 0, rotateDeg) + ofPoint(_x, _y);
    ofPoint b = ofPoint(0, halfSide).rotate(0, 0, rotateDeg) + ofPoint(_x, _y);
    ofPoint c = ofPoint(-halfSide, halfSide).rotate(0, 0, rotateDeg) + ofPoint(_x, _y);
    grid.moveTo(a.x, a.y);
    grid.lineTo(b.x, b.y);
    grid.lineTo(c.x, c.y);
    grid.close();
}
void ofApp::addQtrTriPath2(float _x, float _y, float _s, int _d) {
    float halfSide = _s / 2;
    float rotateDeg = 90 * _d;
    ofPoint a = ofPoint(-halfSide, -halfSide).rotate(0, 0, rotateDeg) + ofPoint(_x, _y);
    ofPoint b = ofPoint(0, -halfSide).rotate(0, 0, rotateDeg) + ofPoint(_x, _y);
    ofPoint c = ofPoint(0, halfSide).rotate(0, 0, rotateDeg) + ofPoint(_x, _y);
    grid.moveTo(a.x, a.y);
    grid.lineTo(b.x, b.y);
    grid.lineTo(c.x, c.y);
    grid.close();
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
