#pragma once

#include "ofMain.h"
#include "ofxCv.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void audioIn(ofSoundBuffer & input);

        vector <float> in;
        vector <float> volHistory;
    
        int bufferCounter;
        int drawCounter;
        float smoothedVol;
        float scaledVol;

        ofVideoGrabber cam;
        ofxCv::FlowFarneback farneback;
        ofxCv::Flow* curFlow;
        ofShader shader;
        ofSoundStream soundStream;
		
};
