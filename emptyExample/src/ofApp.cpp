#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    
}

//void ofApp::drawCircle() {
//
//}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    
    ofPushMatrix();
    ofPath p;
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    p.setStrokeColor(ofColor(255, 255, 255));
    p.setStrokeWidth(2);
    p.setFilled(false);
    p.setCircleResolution(90);
    p.circle(0, 0, 200);
    p.draw();
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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