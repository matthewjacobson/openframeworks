#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    cam.initGrabber(1280, 720);
    
    a = complex<double>(1.0, 0.0);
    b = complex<double>(0.0, 0.0);
    c = complex<double>(0.0, 0.0);
    d = complex<double>(1.0, 0.0);
    
    for (int i = 0; i < 10; i += 1) {
        cout << i << endl;
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    cam.update();
    
//    a.real(100 * ofGetElapsedTimef()); // scaling
//    a.imag(mouseX / 50.0); // rotation + scaling
//    b.real(mouseX / 10000.0); // translate horizontal
//    b.imag(mouseX / 10000.0); // translate vertical
//    c.real(mouseY / 100000.0); // ????? left zooms in/right zooms out
//    c.imag(mouseY / 1000.0); // ????? left zooms out/right zooms in
    d.real(mouseX / 10000000.0); // scaling
    d.imag(mouseY / 10000000.0); // scaling
    
//    a.real(mouseX / 10.0); // scaling
//    a.imag(mouseY / 50.0); // rotation + scaling
    
    // follows the mouse
//    b.real(mouseX);
//    b.imag(mouseY);
    
//    c.real(mouseX / 10000.0); // ????? left zooms in/right zooms out
//    c.imag(mouseY / 10000.0); // ????? left zooms out/right zooms in
    
//    float radius = 5 * (sin(0.2 * ofGetElapsedTimef()) + 0);
//    radius = 1;
//    float xpos = radius * cos(0.3 * ofGetElapsedTimef());
//    float ypos = radius * sin(0.4 * ofGetElapsedTimef());
//    c.real(xpos / 10000.0); // ????? left zooms in/right zooms out
//    c.imag(ypos / 10000.0); // ????? left zooms out/right zooms in
//    a.real(cos(0.1 * ofGetElapsedTimef()));
//    a.imag(sin(0.07 * ofGetElapsedTimef()));
//    cout << mouseX << " " << mouseY << endl;
    
//    d.imag((float) (mouseX + 500) / 10 / ofGetHeight() * 10);
//    c.real((float) (mouseY + 500) / 10 / ofGetWidth() / 100 + 0.01 * ofGetElapsedTimef());
//    a.real(cos(0.5 * ofGetElapsedTimef()));
//    a.imag(sin(0.5 * ofGetElapsedTimef()));
//    c += (double)0.1 * ofGetElapsedTimef();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPixels pixels = cam.getPixels();
    int pw = pixels.getWidth();
    int ph = pixels.getHeight();
    
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    float incr = 1;
    for (float r = -ofGetWidth() / 2; r < ofGetWidth() / 2; r += incr) {
        for (int i = -ofGetHeight() / 2; i < ofGetHeight() / 2; i += incr) {
    
            complex<double> z(r, i);
//            complex<double> t = (z * d - b) / (a - pow(z, 2) * c);
            complex<double> t = (a - b * z) / (c + d * z);
            
//            if ( (((int)(t.real() + 1000000) / 20) % 2 + ((int)(t.imag() + 1000000) / 20) % 2) % 2 == 0 ) ofSetColor(0);
//            else ofSetColor(255);
//            int xc, yc;
            int xc = ((int)t.real() + 1000000) % pw;
            int yc = ((int)t.imag() + 1000000) % ph;
            ofSetColor(pixels.getColor(xc, yc));

            ofDrawCircle(r, i, incr / 2);
            
        }
    }
    
//    cam.draw(0, 0);
    
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
