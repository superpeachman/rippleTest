#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        float getVal(int x, int y);
        void sim();
        void ripple();
    
        int w;//img width
        int h;//img height
        int pixels;//Number of pixel
    
        ofImage image;
        ofImage updatedImage;
    
        vector<float> odata;
        vector<float> ndata;
        vector<float> tempV;

        float eps = 5.0;
        float z = 0.2;
        ofVec3f light = ofVec3f(1, 1, 0);

        bool clickFlag = false;
    
};
