#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "sceneManager.h"

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

	sceneManager sceneMan;
	ofxUICanvas uiCanvas;

	void audioIn(float * input, int bufferSize, int nChannels);
	ofSoundStream soundStream;

	vector <float> left;
	vector <float> right;
	vector <float> vol_buf;
};