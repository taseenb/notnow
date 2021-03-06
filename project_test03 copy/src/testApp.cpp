#include "testApp.h"

// from ProCamToolkit
GLdouble modelviewMatrix[16], projectionMatrix[16];

GLint viewport[4];

void updateProjectionState() {
	glGetDoublev(GL_MODELVIEW_MATRIX, modelviewMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projectionMatrix);
	glGetIntegerv(GL_VIEWPORT, viewport);
}

ofVec3f ofWorldToScreen(ofVec3f world) {
	updateProjectionState();
	GLdouble x, y, z;
	gluProject(world.x, world.y, world.z, modelviewMatrix, projectionMatrix, viewport, &x, &y, &z);
	ofVec3f screen(x, y, z);
	screen.y = ofGetHeight() - screen.y;
	return screen;
}

ofMesh getProjectedMesh(const ofMesh& mesh) {
	ofMesh projected = mesh;
	for(int i = 0; i < mesh.getNumVertices(); i++) {
		ofVec3f cur = ofWorldToScreen(mesh.getVerticesPointer()[i]);
		cur.z = 0;
		projected.setVertex(i, cur);
	}
	return projected;
}

template <class T>
void addTexCoords(ofMesh& to, const vector<T>& from) {
	for(int i = 0; i < from.size(); i++) {
		to.addTexCoord(from[i]);
	}
}

using namespace ofxCv;

void testApp::setup() {
	ofSetFrameRate(30);
	ofSetVerticalSync(true);
	ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
    verticalSetup = false;
    
    // KINECT IR CAMERA
    kinect.init(true); // shows infrared instead of RGB video image
    kinect.open();		// opens first available kinect
    // zero the tilt on startup
	kinectAngle = 30;
	kinect.setCameraTiltAngle(kinectAngle);
    
	// FACE TRACKER
	tracker.setup();
	eyeFbo.allocate(128, 48, GL_RGB);
	runningMean = 24;
	
	osc.setup("localhost", 8338);
    
    // FACE OUTLINE SETTINGS
//    facePath.setFillColor(ofColor(0,0,0));
    //facePath.setStrokeColor(ofColor(255,255,0));
    //facePath.setStrokeWidth(2);
    
    ofBackground(0);
    
    if (verticalSetup) {
        ofSetOrientation(OF_ORIENTATION_90_LEFT);
    }
}

void testApp::update() {
	//cam.update();
    
    // KINECT
    kinect.update();
    
	if(kinect.isFrameNew()) {
        
        if (verticalSetup) {
            kinect.getPixelsRef().rotate90To(rotatedImage, 3);
            tracker.update(toCv(rotatedImage));
            rotatedTexture.loadData(rotatedImage);
        } else {
            tracker.update(toCv(kinect));
        }
        
        position = tracker.getPosition();
		scale = tracker.getScale();
		rotationMatrix = tracker.getRotationMatrix();
		
		if(tracker.getFound()) {
            
			ofVec2f
			leftOuter = tracker.getImagePoint(36),
			leftInner = tracker.getImagePoint(39),
			rightInner = tracker.getImagePoint(42),
			rightOuter = tracker.getImagePoint(45);
			
            
            // Face parts POLYLINES
//            facePolyline = tracker.getImageFeature(ofxFaceTracker::FACE_OUTLINE);
//			leftEyePolyline = tracker.getImageFeature(ofxFaceTracker::LEFT_EYE);
//            rightEyePolyline = tracker.getImageFeature(ofxFaceTracker::RIGHT_EYE);
//            innerMouthPolyline = tracker.getImageFeature(ofxFaceTracker::INNER_MOUTH);
//            outerMouthPolyline = tracker.getImageFeature(ofxFaceTracker::OUTER_MOUTH);
//            noseBasePolyline = tracker.getImageFeature(ofxFaceTracker::NOSE_BASE);
//            noseBridgePolyline = tracker.getImageFeature(ofxFaceTracker::NOSE_BRIDGE);
//            leftEyebrowPolyline = tracker.getImageFeature(ofxFaceTracker::LEFT_EYEBROW);
//            rightEyebrowPolyline = tracker.getImageFeature(ofxFaceTracker::RIGHT_EYEBROW);
            
            
            // Face parts SHAPES
//            facePath = getPathFromPolyline(facePolyline);
//
//			
//			ofVec2f leftCenter = leftEyePolyline.getBoundingBox().getCenter();
//			ofVec2f rightCenter = rightEyePolyline.getBoundingBox().getCenter();
			
//			float leftRadius = (leftCenter.distance(leftInner) + leftCenter.distance(leftOuter)) / 2;
//			float rightRadius = (rightCenter.distance(rightInner) + rightCenter.distance(rightOuter)) / 2;
			
			ofVec2f
			leftOuterObj = tracker.getObjectPoint(36),
			leftInnerObj = tracker.getObjectPoint(39),
			rightInnerObj = tracker.getObjectPoint(42),
			rightOuterObj = tracker.getObjectPoint(45);
			
			ofVec3f upperBorder(0, -3.5, 0), lowerBorder(0, 2.5, 0);
			ofVec3f leftDirection(-1, 0, 0), rightDirection(+1, 0, 0);
			float innerBorder = 1.5, outerBorder = 2.5;
			
			ofMesh leftRect, rightRect;
			leftRect.setMode(OF_PRIMITIVE_LINE_LOOP);
			leftRect.addVertex(leftOuterObj + upperBorder + leftDirection * outerBorder);
			leftRect.addVertex(leftInnerObj + upperBorder + rightDirection * innerBorder);
			leftRect.addVertex(leftInnerObj + lowerBorder + rightDirection * innerBorder);
			leftRect.addVertex(leftOuterObj + lowerBorder + leftDirection * outerBorder);
			rightRect.setMode(OF_PRIMITIVE_LINE_LOOP);
			rightRect.addVertex(rightInnerObj+ upperBorder + leftDirection * innerBorder);
			rightRect.addVertex(rightOuterObj + upperBorder + rightDirection * outerBorder);
			rightRect.addVertex(rightOuterObj + lowerBorder + rightDirection * outerBorder);
			rightRect.addVertex(rightInnerObj + lowerBorder + leftDirection * innerBorder);
			
			ofPushMatrix();
			//ofSetupScreenOrtho(800, 800, OF_ORIENTATION_UNKNOWN, true, -1000, 1000);
			ofScale(1, 1, -1);
			ofTranslate(position);
			applyMatrix(rotationMatrix);
			ofScale(scale, scale, scale);
			leftRectImg = getProjectedMesh(leftRect);
			rightRectImg = getProjectedMesh(rightRect);		
			ofPopMatrix();
			
			// more effective than using object space points would be to use image space
			// but translate to the center of the eye and orient the rectangle in the
			// direction the face is facing.
			/*
			 ofPushMatrix();
			 ofTranslate(tracker.getImageFeature(ofxFaceTracker::LEFT_EYE).getCentroid2D());
			 applyMatrix(rotationMatrix);
			 ofRect(-50, -40, 2*50, 2*40);
			 ofPopMatrix();
			 
			 ofPushMatrix();
			 ofTranslate(tracker.getImageFeature(ofxFaceTracker::RIGHT_EYE).getCentroid2D());
			 applyMatrix(rotationMatrix);
			 ofRect(-50, -40, 2*50, 2*40);
			 ofPopMatrix();
			 */
			
			ofMesh normRect, normLeft, normRight;
			normRect.addVertex(ofVec2f(0, 0));
			normRect.addVertex(ofVec2f(64, 0));
			normRect.addVertex(ofVec2f(64, 48));
			normRect.addVertex(ofVec2f(0, 48));
			normLeft.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
			normRight.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
			normLeft.addVertices(normRect.getVertices());
			normRight.addVertices(normRect.getVertices());
			addTexCoords(normLeft, leftRectImg.getVertices());
			addTexCoords(normRight, rightRectImg.getVertices());
            
			eyeFbo.begin();
			ofSetColor(255);
			ofFill();
			
            kinect.getTextureReference().bind();
            //cam.getTextureReference().bind(); // ??????
			
            normLeft.draw();
			ofTranslate(64, 0);
			normRight.draw();
            
            kinect.getTextureReference().unbind();
			//cam.getTextureReference().unbind(); // ?????
			
            eyeFbo.end();
            
			eyeFbo.readToPixels(eyePixels);
			
			convertColor(eyePixels, gray, CV_RGB2GRAY);
			normalize(gray, gray);
			Sobel(gray, sobelx, CV_32F, 1, 0, 3, 1);
			Sobel(gray, sobely, CV_32F, 0, 1, 3, 1);
			sobel = abs(sobelx) + abs(sobely);
			bitwise_not(gray, gray);
			gray.convertTo(grayFloat, CV_32F);
			sobel += grayFloat;
			
			rowMean = meanRows(sobel);
			// clear the ends
			rowMean.at<float>(0) = 0;
			rowMean.at<float>(rowMean.rows - 1) = 0;
			// build the line
			rowMeanLine.clear();
			float avg = 0, sum = 0;
			for(int i = 0; i < rowMean.rows; i++) {
				float cur = rowMean.at<float>(i);
				avg += i * cur;
				sum += cur;
				rowMeanLine.addVertex(cur, i);
			}
			avg /= sum;
			rowGraph.addSample(avg - runningMean);
			runningMean = 0; //ofLerp(runningMean, avg, .3);
			
			Mat sobelImgMat = toCv(sobelImg);
			imitate(sobelImg, gray);
			sobel.convertTo(sobelImgMat, CV_8U, .5);
			sobelImg.update();
			
			ofxOscMessage msg;
			msg.setAddress("/gesture/blink");
			msg.addIntArg(rowGraph.getState() ? 1 : 0);
			osc.sendMessage(msg);
            
            // FACE OUTLINE UPDATE - WITH EYES
//            faceBoundingBox = facePolyline.getBoundingBox();
//            facePath.clear();
//            
//            if (verticalSetup) {
//                facePath.rectangle(0, 0, 600, 800);
//            } else {
//                facePath.rectangle(0, 0, 800, 600);
//            }
//            
//            for (int i=0; i < facePolyline.size(); i++) {
//                facePath.lineTo(facePolyline[i]);
//            }
//            facePath.close();
//            
//            for (int i=0; i < leftEyePolyline.size(); i++) {
//                facePath.lineTo(leftEyePolyline[i]);
//            }
//            facePath.close();
//            
//            for (int i=0; i < rightEyePolyline.size(); i++) {
//                facePath.lineTo(rightEyePolyline[i]);
//            }
//            facePath.close();
//
            
            
            // ANIMATION
            animations.update(tracker);
            
            
		} else {
            
            animations.clear();
            
            
//            facePath.clear();
        }
	}
    
}


void testApp::draw() {
	ofSetColor(255);
    
    ofPushMatrix();
    ofScale(2, 2, 0);
    
    if (verticalSetup) {
        ofTranslate(-320/2, -240/2);
        rotatedTexture.draw(0,0);
    } else {
        ofTranslate(-480/2, -360/2);
        kinect.draw(0, 0);
    }
    
    // DRAW THE ANIMATION IN THE BOUNDING BOX
    animations.draw();
    
    ofPopMatrix();
    
}


ofPath testApp::getPathFromPolyline(ofPolyline polyLine) {
    
    ofPath path;
    
    for (int i=0; i < polyLine.size(); i++) {
        path.lineTo(polyLine[i]);
    }
    
    return path;
    
}


void testApp::keyPressed(int key) {
	if(key == 'r') {
		tracker.reset();
	}
    
    switch (key) {
        case OF_KEY_UP:
			kinectAngle++;
			if(kinectAngle>30) kinectAngle=30;
			kinect.setCameraTiltAngle(kinectAngle);
			break;
			
		case OF_KEY_DOWN:
			kinectAngle--;
			if(kinectAngle<-30) kinectAngle=-30;
			kinect.setCameraTiltAngle(kinectAngle);
			break;
    }
    
}





