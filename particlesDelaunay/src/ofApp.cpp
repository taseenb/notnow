#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground( 0, 0, 0 );
	ofSetFrameRate( 60 );
    ofEnableSmoothing();
    
    float centerScreenX = ofGetWidth() / 2;
    float centerScreenY = ofGetHeight() / 2;
    
    p1.setInitialCondition(centerScreenX + ofRandom(-100, 100), centerScreenY + ofRandom(-100, 100), 0, 0);
    p2.setInitialCondition(centerScreenX + ofRandom(-100, 100), centerScreenY + ofRandom(-100, 100), 0, 0);
    p3.setInitialCondition(centerScreenX + ofRandom(-100, 100), centerScreenY + ofRandom(-100, 100), 0, 0);
    p4.setInitialCondition(centerScreenX + ofRandom(-100, 100), centerScreenY + ofRandom(-100, 100), 0, 0);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    p1.update();
    p2.update();
    p3.update();
    p4.update();
    
//    ofLog() << p1.pos.x;
//    ofLog() << p1.pos.y;
//    ofLog() << p2.pos.x;
//    ofLog() << p2.pos.y;
    
    triangulation.reset();
    
    triangulation.addPoint(ofPoint(p1.pos.x,p1.pos.y));
    triangulation.addPoint(ofPoint(p2.pos.x,p2.pos.y));
    triangulation.addPoint(ofPoint(p3.pos.x,p3.pos.y));
    triangulation.addPoint(ofPoint(p4.pos.x,p4.pos.y));
    
    triangulation.triangulate();
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofNoFill();
    ofSetColor(255, 255, 255);
    ofRect(200, 200, 200, 200);
    
    triangulation.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
