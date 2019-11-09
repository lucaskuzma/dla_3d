#include "ofApp.h"

#define SIZE 128

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);

    // we're going to load a ton of points into an ofMesh
    mesh.setMode(OF_PRIMITIVE_POINTS);

    ofVec3f p(0, 0, 0);
    mesh.addVertex(p);
    frozen.push_back(p);

    ofEnableDepthTest();
    glEnable(GL_POINT_SMOOTH); // use circular points instead of square points
    glPointSize(3); // make the points bigger
}

//--------------------------------------------------------------
void ofApp::update(){
    // spawn a point
    ofVec3f p(ofRandom(-SIZE, SIZE), ofRandom(-SIZE, SIZE), ofRandom(-SIZE, SIZE));
    moving.push_back(p);
    
    //
    int numVerts = mesh.getNumVertices();
    for (int i=0; i<numVerts; ++i) {
        ofVec3f v = mesh.getVertex(i);

        mesh.setVertex(i, v);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor::gray, ofColor::black, OF_GRADIENT_CIRCULAR);

    cam.begin();
    ofScale(2, -2, 2); // flip the y axis and zoom in a bit
    ofRotateYDeg(90);
    mesh.draw();
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
