#ifndef __project_test03__CrazyEyes__
#define __project_test03__CrazyEyes__

#include <iostream>
#include "ofMain.h"

#include "BaseAnimation.h"


class CrazyEyes : public BaseAnimation {
    
    public:
        void update(ofxFaceTrackerThreaded & tracker);
        void draw();
        void drawCircle(int x, int y, int radius);
    
    float leftEyeRadius, rightEyeRadius;
    
    ofPoint noseCenter, leftEyeCenter, rightEyeCenter;
    
    
    
};


#endif