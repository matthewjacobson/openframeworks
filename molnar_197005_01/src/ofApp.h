#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofPath getLineFill(ofPolyline _p, float _s, float _t);
        void addFullBoxPath(float _x, float _y, float _s);
        void addHalfRectPath(float _x, float _y, float _s, int _d);
        void addHalfTriPath(float _x, float _y, float _s, int _d);
        void addQtrTriPath1(float _x, float _y, float _s, int _d);
        void addQtrTriPath2(float _x, float _y, float _s, int _d);
		
        ofPath grid;
        float framePad;
        int countBoxes;
};
