#include <iostream>
#include "ofMain.h"
#include "particle.h"


class GeneralAnimations : public ofBaseApp {
    
    public:
        void setup();
        void update(ofPolyline facePolyline_,
                ofPolyline leftEyePolyline,
                ofPolyline rightEyePolyline,
                ofPolyline innerMouthPolyline,
                ofPolyline outerMouthPolyline,
                ofPolyline noseBasePolyline,
                ofPolyline noseBridgePolyline,
                ofPolyline leftEyebrowPolyline,
                ofPolyline rightEyebrowPolyline);
        void draw();
        ofPath getPathFromPolyline(ofPolyline polyLine);
        void drawCircle(int x, int y, int radius);
    
        // ANIMATIONS
        void crazyEyesAnimation();
    
        int x, y, w, h,
    faceCenterX, faceCenterY, noseCenterX, noseCenterY;
    
    ofPoint noseCenter, leftEyeCenter, rightEyeCenter;
    
    float leftEyeRadius, rightEyeRadius;
    
    
    ofPath facePath;
    ofPath leftEyePath;
    ofPath rightEyePath;
    ofPath innerMouthPath;
    ofPath outerMouthPath;
    ofPath noseBasePath;
    ofPath noseBridgePath;
    ofPath leftEyebrowPath;
    ofPath rightEyebrowPath;

    ofPolyline facePolyline;
    ofPolyline leftEyePolyline;
    ofPolyline rightEyePolyline;
    ofPolyline innerMouthPolyline;
    ofPolyline outerMouthPolyline;
    ofPolyline noseBasePolyline;
    ofPolyline noseBridgePolyline;
    ofPolyline leftEyebrowPolyline;
    ofPolyline rightEyebrowPolyline;
    
    
    particle p;
    
    
};