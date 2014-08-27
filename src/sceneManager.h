//
//  sceneManager.h
//  natnetTracker
//
//  Created by Ovis aries on 2014/08/25.
//
//

#ifndef __natnetTracker__sceneManager__
#define __natnetTracker__sceneManager__

#include "ofMain.h"
#include "ofxOsc.h"

#include "paramBox.h"
#include "trackingManager.h"

#include "trackerBaseScene.h"
#include "tracker_sequence.h"
#include "tracker_angle.h"
#include "trail.h"

class sceneManager{
public:
	void setup();
	void update();
	void draw();

	void debugFunc();

	vector<trackerBaseScene*> scenes;
	ofxOscReceiver receiver;

	trackingManager tracker;
	ofFbo masterBuf;

	bool viewCircleTrack;
	bool viewTestPattern;
	bool checkBoard;

	paramBox pBox;
};

#endif /* defined(__natnetTracker__sceneManager__) */
