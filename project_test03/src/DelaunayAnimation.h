#ifndef __project_test03__Delaunay__
#define __project_test03__Delaunay__


#include <iostream>
#include "ofMain.h"

#include "BaseAnimation.h"
#include "ofxDelaunay.h"


class DelaunayAnimation : public BaseAnimation {
    
public:
    void update(ofxFaceTrackerThreaded & tracker);
    void draw();
    
    ofxDelaunay triangulation;
    
};

#endif
