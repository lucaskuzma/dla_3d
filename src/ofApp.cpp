#include "ofApp.h"

#define SIZE 4096   // make this always bigger than bounding sphere
#define STEP 0.9    // wiggle step
#define FREEZE_THRESHOLD 4 // how close points have to be to freeze
#define SPAWN_DISTANCE 2   // how far from bounding sphere surface we spawn
#define GROWTH_FACTOR 0.01 // how many wiggly points to aim for, given sphere volume
#define MAX_MOVING 100     // how many moving particles at most
#define SIM_SPEED 200      // how many sim steps per frame

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackground(0, 0, 0);

    frozen.setMode(OF_PRIMITIVE_POINTS);
    moving.setMode(OF_PRIMITIVE_POINTS);

    ofVec3f p(0, 0, 0);
    frozen.addVertex(p);
    frozen.addColor(ofFloatColor(1.0, 1.0, 1.0));
    boundingRadius = 0;
    
    runSim = true;

    ofEnableDepthTest();
    glEnable(GL_POINT_SMOOTH);
    glPointSize(2);
}

//--------------------------------------------------------------
void ofApp::update(){
    // update multiple time steps per frame
    for (int i=0; i<SIM_SPEED && runSim; i++){
        this->updateSim();
    }
}

//--------------------------------------------------------------
void ofApp::updateSim(){
    // spawn a point
    float spawnRadius = boundingRadius + SPAWN_DISTANCE;
    if (moving.getNumVertices() < spawnRadius * spawnRadius * spawnRadius * GROWTH_FACTOR
        && moving.getNumVertices() < MAX_MOVING) {
        ofVec3f p(ofRandom(-SIZE, SIZE), ofRandom(-SIZE, SIZE), ofRandom(-SIZE, SIZE));
        moving.addVertex(p);
        moving.addColor(ofFloatColor(0.3, 0.3, 0.3));
    }

    // wiggle
    int movingVerts = moving.getNumVertices();
    for (int i=0; i<movingVerts; ++i) {
        ofVec3f v = moving.getVertex(i);
        v += ofVec3f(ofRandom(-STEP, STEP), ofRandom(-STEP, STEP), ofRandom(-STEP, STEP));
        v.limit(spawnRadius);
        moving.setVertex(i, v);
        
        // find near points
        int frozenVerts = frozen.getNumVertices();
        for (int j=0; j<frozenVerts; ++j) {
            ofVec3f f = frozen.getVertex(j);
            if (f.squareDistance(v) < FREEZE_THRESHOLD) {
                freezeList.push_back(i);
                break;
            }
        }
    }
    
    // freeze near points
    while (!freezeList.empty())
    {
        // freeze point
        int i = freezeList.back();
        ofVec3f v = moving.getVertex(i);
        moving.removeVertex(i);
        frozen.addVertex(v);
        frozen.addColor(ofFloatColor(1.0, 1.0, 1.0));
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
    ofRotateYDeg(ofGetElapsedTimef() * 5.0);
    frozen.draw();
    moving.draw();
    cam.end();
    
    ofDrawBitmapString(ofToString(frozen.getNumVertices()) + " " + ofToString(moving.getNumVertices()), 10, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' '){
        runSim = !runSim;
    }
    if (key == 's') {
        frozen.save("mesh.ply");
    }
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
