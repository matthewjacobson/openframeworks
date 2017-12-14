#include "letter.h"
letter::letter() {
}

void letter::setup(vector<vector<ofPoint>> _p) {
    points = _p;
    getCenter();
}

void letter::getCenter() {
    ofPoint c = ofPoint(0, 0);
    int count = 0;
    for (int i = 0; i < points.size(); i++) {
        for (int j = 0; j < points[i].size(); j++) {
            c += points[i][j];
            count++;
        }
    }
    center = c / count;
}

void letter::draw() {
    ofBeginShape();
        for (int i = 0; i < points.size(); i++) {
            for (int j = 0; j < points[i].size(); j++) {
                ofPoint p = points[i][j];
                ofVertex(p);
            }
            ofNextContour(TRUE);
        }
    ofEndShape();
}
