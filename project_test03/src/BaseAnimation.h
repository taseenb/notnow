#ifndef __project_test03__BaseAnimation__
#define __project_test03__BaseAnimation__

#include <iostream>
#include "ofMain.h"
#include "ofxFaceTrackerThreaded.h"


class BaseAnimation : public ofBaseApp {
    
    public:
        //void setup();
        void update(ofxFaceTrackerThreaded & tracker);
        void draw();
    
    ofPath getPathFromPolyline(ofPolyline polyLine);
    
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
    
    float leftEyeRadius, rightEyeRadius;
    
    ofPoint noseCenter, leftEyeCenter, rightEyeCenter;
    
    
    // FRAME BUFFER OBJECT
    ofFbo animFbo; // animFbo.allocate(400, 400, GL_RGBA);
    
};


#endif

