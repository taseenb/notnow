#include "BaseAnimation.h"

void BaseAnimation::update(ofxFaceTrackerThreaded tracker) {
    
    facePolyline = tracker.getImageFeature(ofxFaceTracker::FACE_OUTLINE);
    leftEyePolyline = tracker.getImageFeature(ofxFaceTracker::LEFT_EYE);
    rightEyePolyline = tracker.getImageFeature(ofxFaceTracker::RIGHT_EYE);
    innerMouthPolyline = tracker.getImageFeature(ofxFaceTracker::INNER_MOUTH);
    outerMouthPolyline = tracker.getImageFeature(ofxFaceTracker::OUTER_MOUTH);
    noseBasePolyline = tracker.getImageFeature(ofxFaceTracker::NOSE_BASE);
    noseBridgePolyline = tracker.getImageFeature(ofxFaceTracker::NOSE_BRIDGE);
    leftEyebrowPolyline = tracker.getImageFeature(ofxFaceTracker::LEFT_EYEBROW);
    rightEyebrowPolyline = tracker.getImageFeature(ofxFaceTracker::RIGHT_EYEBROW);
    
    facePath = getPathFromPolyline(facePolyline);
    leftEyePath = getPathFromPolyline(leftEyePolyline);
    rightEyePath = getPathFromPolyline(rightEyePolyline);
    innerMouthPath = getPathFromPolyline(innerMouthPolyline);
    outerMouthPath = getPathFromPolyline(outerMouthPolyline);
    noseBasePath = getPathFromPolyline(noseBasePolyline);
    noseBridgePath = getPathFromPolyline(noseBridgePolyline);
    leftEyebrowPath = getPathFromPolyline(leftEyebrowPolyline);
    rightEyebrowPath = getPathFromPolyline(rightEyebrowPolyline);

}

void BaseAnimation::draw() {
    
    //    for (int i=0; i<facePolyline.size(); i++) {
    //        ofLine(facePolyline[i].x, facePolyline[i].y, noseCenter.x, noseCenter.y);
    //    }
    
}



ofPath BaseAnimation::getPathFromPolyline(ofPolyline polyLine) {
    ofPath path;
    for (int i=0; i < polyLine.size(); i++) {
        path.lineTo(polyLine[i]);
    }
    return path;
}
