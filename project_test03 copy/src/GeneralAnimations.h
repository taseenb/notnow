#ifndef __project_test03__GeneralAnimations__
#define __project_test03__GeneralAnimations__


#include <iostream>
#include "ofMain.h"
//#include "ofxFaceTrackerThreaded.h"

// Animations
#include "CrazyEyes.h"


class GeneralAnimations : public ofBaseApp {
    
    public:
        void update(ofxFaceTrackerThreaded & tracker);
        void draw();
        void blend();
        void clear();
    
    // List of animations
    CrazyEyes crazyEyesAnim;
    
};


#endif