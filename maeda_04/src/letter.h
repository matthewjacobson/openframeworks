#include "ofMain.h" // we need to include this to have a reference to the openFrameworks framework
class letter {
    
public:
    
    void setup(vector<vector<ofPoint>> _p);
    void getCenter();
    void draw();
    
    vector<vector<ofPoint>> points;
    ofPoint center;
    
    letter();
    
};
