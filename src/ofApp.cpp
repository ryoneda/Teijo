#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(0);
    shader.load("shader");
    
    cam.setDeviceID(0);
    cam.setDesiredFrameRate(10);
    cam.initGrabber(320, 240);
    
    curFlow = &farneback;
    
    soundStream.printDeviceList();
    int bufferSize = 256;

    in.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);
    
    bufferCounter    = 0;
    drawCounter        = 0;
    scaledVol        = 0.0;

    ofSoundStreamSettings settings;
    
    auto devices = soundStream.getMatchingDevices("default");
    if(!devices.empty()){
        settings.setInDevice(devices[0]);
    }

    settings.setInListener(this);
    settings.sampleRate = 44100;
    settings.numOutputChannels = 0;
    settings.numInputChannels = 1;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
}

void ofApp::update() {
    cam.update();
    if (cam.isFrameNew()) {
        curFlow = &farneback;
    }
    curFlow->calcOpticalFlow(cam);
    
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.2, 1.0, true);
}

void ofApp::draw() {
    
    cout << farneback.getAverageFlow() << endl;

    shader.begin();
    shader.setUniform1f("time", ofGetElapsedTimef());
    shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    shader.setUniform2f("flow", farneback.getAverageFlow());
    shader.setUniform1f("vol", scaledVol);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
    
}

void ofApp::audioIn(ofSoundBuffer & input){
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;

    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (size_t i = 0; i < input.getNumFrames(); i++){
        in[i]        = input[i]*0.5;
        curVol += in[i] * in[i];
        numCounted++;
    }
    
    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
//    色を変えてあげる
//    動きを分かりやすく
//    色んな色がグニャグニャグニャ
//    目的を明確に
//    社会に実装する時
//    場所にあった変数
//    どうなるのか建築的にも
//    澱んだものは死んでいく
//    機械はフラットに認知，人間はフォーカス　それを気づかせる
}
