#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    framePad = 1.5;
    countPoints = 1000;
    offsetRadius = 50;
    minZoom = 1;
    maxZoom = 5;
    //minZoom = 0.1;
    //maxZoom = 1;
    
    camWidth = ofGetWidth();
    camHeight = ofGetHeight();
    
    myVideoGrabber.initGrabber(camWidth, camHeight);
    myTexture.allocate(camWidth, camHeight, GL_RGB);
    
    for (int i = 0; i < countPoints; i++) {
        float x = framePad * ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2);
        float y = framePad * ofRandom(-ofGetHeight() / 2, ofGetHeight() / 2);
        triangulation.addPoint(ofPoint(x,y));
    }
    triangulation.triangulate();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // Ask the grabber to refresh its data.
    myVideoGrabber.update();
    
    // If the grabber indeed has fresh data,
    if(myVideoGrabber.isFrameNew()){
        
        // Obtain a pointer to the grabber's image data.
        ofPixels pixelData = myVideoGrabber.getPixels();
        
        // Now stash the inverted data in an ofTexture
        myTexture.allocate(pixelData);
        
        myTexture.bind();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    vector<ofMeshFace> faces = triangulation.triangleMesh.getUniqueFaces();
    
    ofSetColor(255);
    for (int i = 0; i < faces.size(); i++) {
        
        ofMeshFace face = faces[i];
        ofPoint p0 = face.getVertex(0);
        ofPoint p1 = face.getVertex(1);
        ofPoint p2 = face.getVertex(2);
        
        ofPoint centroid = ofPoint((p0.x + p1.x + p2.x) / 3, (p0.y + p1.y + p2.y) / 3);
        
        ofPoint transTexToCenter = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);
        
        float thetaNoise = 2 * PI * ofxeasing::map(ofSignedNoise(p0.x / ofGetWidth(), p0.y / ofGetHeight()), -1, 1, -1, 1, ofxeasing::sine::easeInOut);
        ofPoint randOffset = ofPoint(offsetRadius * cos(thetaNoise + ofGetElapsedTimef()), offsetRadius * sin(thetaNoise + ofGetElapsedTimef()));
        
        float scale = ofMap(sin(thetaNoise + 1 * ofGetElapsedTimef()), -1, 1, minZoom, maxZoom);
        ofPoint t0 = (p0 - centroid).rotateRad(thetaNoise + ofGetElapsedTimef(), ofVec3f(0, 0, 1)) * scale + centroid;
        ofPoint t1 = (p1 - centroid).rotateRad(thetaNoise + ofGetElapsedTimef(), ofVec3f(0, 0, 1)) * scale + centroid;
        ofPoint t2 = (p2 - centroid).rotateRad(thetaNoise + ofGetElapsedTimef(), ofVec3f(0, 0, 1)) * scale + centroid;
        
        ofMesh newFace;
        newFace.addVertex(p0);
        newFace.addTexCoord(t0 + randOffset + transTexToCenter);
        newFace.addVertex(p1);
        newFace.addTexCoord(t1 + randOffset + transTexToCenter);
        newFace.addVertex(p2);
        newFace.addTexCoord(t2 + randOffset + transTexToCenter);
        newFace.draw();
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
