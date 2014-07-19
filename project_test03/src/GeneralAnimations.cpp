#include "GeneralAnimations.h"


void GeneralAnimations::setup() {
    
    
    
}


void GeneralAnimations::update(ofPolyline facePolyline_,
                               ofPolyline leftEyePolyline_,
                               ofPolyline rightEyePolyline_,
                               ofPolyline innerMouthPolyline_,
                               ofPolyline outerMouthPolyline_,
                               ofPolyline noseBasePolyline_,
                               ofPolyline noseBridgePolyline_,
                               ofPolyline leftEyebrowPolyline_,
                               ofPolyline rightEyebrowPolyline_) {
    
    
    // FACE
    facePolyline = facePolyline_;
    leftEyePolyline = leftEyePolyline_;
    rightEyePolyline = rightEyePolyline_;
    innerMouthPolyline = innerMouthPolyline_;
    outerMouthPolyline = outerMouthPolyline_;
    noseBasePolyline = noseBasePolyline_;
    noseBridgePolyline = noseBridgePolyline_;
    leftEyebrowPolyline = leftEyebrowPolyline_;
    rightEyebrowPolyline = rightEyebrowPolyline_;
    
    facePath = getPathFromPolyline(facePolyline);
    leftEyePath = getPathFromPolyline(leftEyePolyline);
    rightEyePath = getPathFromPolyline(rightEyePolyline);
    innerMouthPath = getPathFromPolyline(innerMouthPolyline);
    outerMouthPath = getPathFromPolyline(outerMouthPolyline);
    noseBasePath = getPathFromPolyline(noseBasePolyline);
    noseBridgePath = getPathFromPolyline(noseBridgePolyline);
    leftEyebrowPath = getPathFromPolyline(leftEyebrowPolyline);
    rightEyebrowPath = getPathFromPolyline(rightEyebrowPolyline);
    
    
    // FACE BOUNDING BOX
    ofRectangle faceBoundingBox = facePolyline.getBoundingBox();
    x = faceBoundingBox.getLeft();
    y = faceBoundingBox.getTop();
    faceCenterX = faceBoundingBox.getCenter().x; // bounding box center X
    faceCenterY = faceBoundingBox.getCenter().y; // bounding box center Y
    w = faceBoundingBox.getWidth();
    h = faceBoundingBox.getHeight();
    
    noseCenter = noseBasePolyline.getBoundingBox().getCenter();
    leftEyeCenter = leftEyePolyline.getBoundingBox().getCenter();
    rightEyeCenter = rightEyePolyline.getBoundingBox().getCenter();

    // PARTICLE
    p.addForce(0.01,0.01);
    p.update();
}


void GeneralAnimations::draw() {
    
//    for (int i=0; i<facePolyline.size(); i++) {
//        ofLine(facePolyline[i].x, facePolyline[i].y, noseCenter.x, noseCenter.y);
//    }
    
    
    p.draw();
    
    //crazyEyesAnimation();
}


void GeneralAnimations::crazyEyesAnimation() {
    
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


ofPath GeneralAnimations::getPathFromPolyline(ofPolyline polyLine) {
    ofPath path;
    for (int i=0; i < polyLine.size(); i++) {
        path.lineTo(polyLine[i]);
    }
    return path;
}

void GeneralAnimations::drawCircle(int x, int y, int radius) {
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



