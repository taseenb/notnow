#include "CrazyEyes.h"


void CrazyEyes::update(ofxFaceTrackerThreaded & tracker) {
    
    noseCenter = noseBasePolyline.getBoundingBox().getCenter();
    leftEyeCenter = leftEyePolyline.getBoundingBox().getCenter();
    rightEyeCenter = rightEyePolyline.getBoundingBox().getCenter();
    
}


void CrazyEyes::draw() {

    leftEyeRadius = sin(ofGetFrameNum()* 0.5f );
    rightEyeRadius = sin(ofGetFrameNum()* 0.5f );
    
    ofNoFill();
    ofSetLineWidth(2);
    ofSetColor(255, 255, 255);
    
    for (int i=0; i<5; i++) {
        drawCircle(leftEyeCenter.x, leftEyeCenter.y, leftEyeRadius+ i*4);
        drawCircle(rightEyeCenter.x, rightEyeCenter.y, rightEyeRadius+ i*4);
    }

}


void CrazyEyes::drawCircle(int x, int y, int radius) {
    ofPushMatrix();
    ofPath p;
    ofTranslate(x, y);
    p.setStrokeColor(ofColor(255, 255, 255));
    p.setStrokeWidth(2);
    p.setFilled(false);
    p.setCircleResolution(90);
    p.circle(0, 0, radius);
    p.draw();
    ofPopMatrix();
}