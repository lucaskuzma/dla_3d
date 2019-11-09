#include "ofApp.h"

#define SIZE 128
#define STEP .1
#define THRESH 30

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

    ofEnableDepthTest();
    glEnable(GL_POINT_SMOOTH); // use circular points instead of square points
    glPointSize(3); // make the points bigger
}

//--------------------------------------------------------------
void ofApp::update(){
    // spawn a point
    ofVec3f p(ofRandom(-SIZE, SIZE), ofRandom(-SIZE, SIZE), ofRandom(-SIZE, SIZE));
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
            if (f.distance(v) < THRESH) {
                addList.push_back(i);
            }
        }
    }
    
    while (!addList.empty())
    {
        int i = addList.back();
        ofVec3f v = moving.getVertex(i);
        moving.removeVertex(i);
        frozen.addVertex(v);
        frozen.addColor(ofFloatColor(1.0, 0.0, 0.0));
        addList.pop_back();
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
