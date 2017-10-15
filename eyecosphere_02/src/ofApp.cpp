#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    subdivisions = 2;
    
    camWidth = ofGetWidth();
    camHeight = ofGetHeight();
    
    myVideoGrabber.initGrabber(camWidth, camHeight);
    myTexture.allocate(camWidth, camHeight, GL_RGB);
    myTracker.setup();
    
    m = ofMesh::icosphere(400, subdivisions);
    
    trackingFeature = ofxFaceTracker2Landmarks::OUTER_MOUTH;
    
    ofHideCursor();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // Ask the grabber to refresh its data.
    myVideoGrabber.update();
    
    // If the grabber indeed has fresh data,
    if(myVideoGrabber.isFrameNew()){
        
        myTracker.update(myVideoGrabber);
        
        // Obtain a pointer to the grabber's image data.
        ofPixels pixelData = myVideoGrabber.getPixels();
        
        // Now stash the inverted data in an ofTexture
        myTexture.allocate(pixelData);
        
        myTexture.bind();
    }
    
    if (myTracker.getInstances().size() > 0) {
        if (fmod(ofGetElapsedTimef() / 5, 2) < 1) trackingFeature = ofxFaceTracker2Landmarks::RIGHT_EYE;
        else trackingFeature = ofxFaceTracker2Landmarks::LEFT_EYE;
        ofRectangle target_boundingbox = myTracker.getInstances()[0].getLandmarks().getImageFeature(trackingFeature).getBoundingBox();
        target = 0.95 * target + 0.05 * ofPoint(target_boundingbox.x + target_boundingbox.width / 2, target_boundingbox.y + target_boundingbox.height / 2);
    }
    else {
        target = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    vector<ofMeshFace> faces = m.getUniqueFaces();
    for (int j = 0; j < faces.size(); j++) {
        ofMeshFace face = faces[j];
        ofPoint p0 = face.getVertex(0);
        ofPoint p1 = face.getVertex(1);
        ofPoint p2 = face.getVertex(2);
        p0.rotate(360 * ofSignedNoise(0.05 * ofGetElapsedTimef()), ofVec3f(0, 0, 1));
        p1.rotate(360 * ofSignedNoise(0.05 * ofGetElapsedTimef()), ofVec3f(0, 0, 1));
        p2.rotate(360 * ofSignedNoise(0.05 * ofGetElapsedTimef()), ofVec3f(0, 0, 1));
        p0.rotate(360 * ofSignedNoise(0.06 * ofGetElapsedTimef()), ofVec3f(0, 1, 0));
        p1.rotate(360 * ofSignedNoise(0.06 * ofGetElapsedTimef()), ofVec3f(0, 1, 0));
        p2.rotate(360 * ofSignedNoise(0.06 * ofGetElapsedTimef()), ofVec3f(0, 1, 0));
        p0.rotate(360 * ofSignedNoise(0.07 * ofGetElapsedTimef()), ofVec3f(1, 0, 0));
        p1.rotate(360 * ofSignedNoise(0.07 * ofGetElapsedTimef()), ofVec3f(1, 0, 0));
        p2.rotate(360 * ofSignedNoise(0.07 * ofGetElapsedTimef()), ofVec3f(1, 0, 0));
        ofPoint c = (p0 + p1 + p2) / 3;
        
        if (c.z < 0) {
            float r = ofMap(mouseX, 0, ofGetWidth(), 50, 300);
            float t = 0;
            ofSetColor(255, MIN(ofMap(c.z, 0, -200, 0, 255), 255));
            ofMesh newFace;
            newFace.addVertex(p0);
            newFace.addTexCoord(ofPoint(r * cos(t), r * sin(t), 0) + target);
            t += 2 * PI / 3;
            newFace.addVertex(p1);
            newFace.addTexCoord(ofPoint(r * cos(t), r * sin(t), 0) + target);
            t += 2 * PI / 3;
            newFace.addVertex(p2);
            newFace.addTexCoord(ofPoint(r * cos(t), r * sin(t), 0) + target);
            newFace.draw();
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == OF_KEY_LEFT && subdivisions > 0) subdivisions--;
    if (key == OF_KEY_RIGHT) subdivisions++;
        
    m = ofMesh::icosphere(350, subdivisions);
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
