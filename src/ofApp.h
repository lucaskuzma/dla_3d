#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

    ofEasyCam cam;
    ofMesh moving;
    ofMesh frozen;
    ofMesh ignore;
    
    vector<int> freezeList;
    float boundingRadius;
    
    bool runSim;
    
	public:
		void setup();
		void update();
        void updateSim();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
};
