#include "DelaunayAnimation.h"


void DelaunayAnimation::update(ofxFaceTrackerThreaded & tracker) {
    
    BaseAnimation::update(tracker);
    
    ofPoint outerMouthCenter = outerMouthPolyline.getBoundingBox().getCenter();
    vector<ofPoint> noseBridgeVertices = noseBridgePolyline.getVertices();
    
    triangulation.reset();
    
    triangulation.addPoint(noseCenter);
    triangulation.addPoint(leftEyeCenter);
    triangulation.addPoint(rightEyeCenter);
    triangulation.addPoint(outerMouthCenter);
    
    // FACE POINTS
    for (int i=0; i<facePolyline.size(); i++) {
        triangulation.addPoint(ofPoint(facePolyline[i].x, facePolyline[i].y));
    }
    
    // NOSE BRIDGE POINTS
    for (int i=0; i<noseBridgePolyline.size(); i++) {
        triangulation.addPoint(ofPoint(noseBridgeVertices[i].x, noseBridgeVertices[i].y));
    }
    
//    ofLog() << noseCenter.x;
//    ofLog() << noseCenter.y;
    
    triangulation.triangulate();
    
}


void DelaunayAnimation::draw() {
    
    //ofNoFill();
    //ofSetColor(ofRandom(255), 0, 0);
    
    // Triangle colors
    ofMesh trianglesMesh = triangulation.triangleMesh;
    trianglesMesh.enableColors();
    
    //triangles.setMode(OF_PRIMITIVE_TRIANGLES);
    trianglesMesh.addColor(ofFloatColor(255.0, 0.0, 0.0));
    
//    vector< ofMeshFace > triangleFaces = trianglesMesh.getUniqueFaces();
//    int n = triangleFaces.size();
//    for (int i=0; i<n; i++) {
//        triangleFaces[i].setColor(0, ofColor(255, 0, 0));
//    }

//    int n = trianglesMesh.getNumIndices();
//    for (int i=0; i<n; i++) {
//        ofPoint p = trianglesMesh.getVertex(i);
//        trianglesMesh.setVertex(i, p);
//        trianglesMesh.setColor(i, ofFloatColor(255, 0, 0));
//    }
    
    trianglesMesh.draw(OF_MESH_FILL);
    
//    ofNoFill();
//    ofSetColor(255, 0, 0);
//    triangulation.draw();
    
}