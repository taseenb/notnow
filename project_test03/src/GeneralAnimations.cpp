#include "GeneralAnimations.h"


void GeneralAnimations::update(ofxFaceTrackerThreaded & tracker) {
    
    delaunayAnim.update(tracker);
    
}


void GeneralAnimations::draw() {
    
    delaunayAnim.draw();
    
}




void GeneralAnimations::blend() {
    
    
    
}


void GeneralAnimations::clear() {
    
//    ofFill();
//    ofSetColor(255, 0, 0);
//    ofRectangle(0,0,ofGetWidth(), ofGetHeight());
    
}





