#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0);
    
    for (int i = 0; i < 1000; i++) {
        boid b(ofRandomWidth(), ofRandomHeight());
        boids.push_back(b);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    quadtree qt(ofRectangle(0, 0, ofGetWidth(), ofGetHeight()), 4);
    
    for (int i = 0; i < boids.size(); i++) {
        qt.insert(&boids[i]);
    }
    
    for (int i = 0; i < boids.size(); i++) {
        float r = 0.005;
        float a = 2 * PI * ofNoise(boids[i].position.x / 1000, boids[i].position.y / 1000, 0.1 * ofGetElapsedTimef());
        boids[i].applyForce(ofVec3f(r * cos(a), r * sin(a)));
//        boids[i].run(boids);
        
        float w = 50;
        float h = 50;
        boids[i].run(qt.query(ofRectangle(boids[i].position.x - w / 2, boids[i].position.y - h / 2, w, h)));
        
        if (boids[i].trail.getVertices().size() > 500) {
            boids[i].trail.getVertices().erase(boids[i].trail.getVertices().begin());
        }
//        boids[i].trail.addVertex(boids[i].position);
        boids[i].trail.getVertices().push_back(boids[i].position);
        boids[i].trail.addColor(ofColor::fromHsb(ofMap(atan2(boids[i].velocity.y, boids[i].velocity.x), -PI, PI, 0, 255), 255, 255, 100));
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    for (int i = 0; i < boids.size(); i++) {
//        ofSetCircleResolution(3);
//        ofSetLineWidth(1);
//        ofSetColor(ofColor::fromHsb(ofMap(atan2(boids[i].velocity.y, boids[i].velocity.x), -PI, PI, 0, 255), 255, 255));
//        ofNoFill();
//        ofPushMatrix();
//            ofTranslate(boids[i].position.x, boids[i].position.y);
//            ofRotate(atan2(boids[i].velocity.y, boids[i].velocity.x) / (2 * PI) * 360);
//            ofDrawCircle(0, 0, 5, 5);
////            ofDrawLine(0, 0, 10, 0);
//        ofPopMatrix();
        boids[i].trail.draw();
    }

    
    ofSetColor(255, 255, 255);
    ofDrawBitmapString(ofToString((int) ofGetFrameRate()) + " fps", 32, 32);
    
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

    for (int i = 0; i < boids.size(); i++) {
        boids[i].applyForce(0.01 * (boids[i].position - ofVec3f(x, y, 0)).normalize());
    }
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
