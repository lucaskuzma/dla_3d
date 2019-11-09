#include "ofApp.h"

#define SIZE 128
#define STEP .1
#define FREEZE_THRESHOLD 10
#define SPAWN_DISTANCE 10

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackground(0, 0, 0);

    // we're going to load a ton of points into an ofMesh
    frozen.setMode(OF_PRIMITIVE_POINTS);
    moving.setMode(OF_PRIMITIVE_POINTS);

    ofVec3f p(0, 0, 0);
    frozen.addVertex(p);
    frozen.addColor(ofFloatColor(1.0, 0.0, 0.0));
    boundingRadius = 0;

    ofEnableDepthTest();
    glEnable(GL_POINT_SMOOTH); // use circular points instead of square points
    glPointSize(3); // make the points bigger
}

//--------------------------------------------------------------
void ofApp::update(){
    // spawn a point
    ofVec3f p(ofRandom(-SIZE, SIZE), ofRandom(-SIZE, SIZE), ofRandom(-SIZE, SIZE));
    p.limit(boundingRadius + SPAWN_DISTANCE);
    moving.addVertex(p);
    
    // wiggle
    int movingVerts = moving.getNumVertices();
    for (int i=0; i<movingVerts; ++i) {
        ofVec3f v = moving.getVertex(i);
        v += ofVec3f(ofRandom(-STEP, STEP), ofRandom(-STEP, STEP), ofRandom(-STEP, STEP));
        moving.setVertex(i, v);
        
        int frozenVerts = frozen.getNumVertices();
        for (int j=0; j<frozenVerts; ++j) {
            ofVec3f f = frozen.getVertex(j);
            if (f.distance(v) < FREEZE_THRESHOLD) {
                freezeList.push_back(i);
            }
        }
    }
    
    while (!freezeList.empty())
    {
        // freeze point
        int i = freezeList.back();
        ofVec3f v = moving.getVertex(i);
        moving.removeVertex(i);
        frozen.addVertex(v);
        frozen.addColor(ofFloatColor(1.0, 0.0, 0.0));
        freezeList.pop_back();
        
        // adjust bounds
        if (v.length() > boundingRadius) {
            boundingRadius = v.length();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    ofScale(2, -2, 2); // flip the y axis and zoom in a bit
    ofRotateYDeg(90);
    frozen.draw();
    moving.draw();
    cam.end();
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
