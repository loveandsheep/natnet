//
//  trackerBaseScene.h
//  natnetTracker
//
//  Created by Ovis aries on 2014/08/26.
//
//

#ifndef __natnetTracker__trackerBaseScene__
#define __natnetTracker__trackerBaseScene__

#include "ofMain.h"
#include "ofxOsc.h"

#include "paramBox.h"
#include "trackingManager.h"


class trackerBaseScene{
public:
	virtual void setup();
	virtual void update();
	virtual void draw();
	virtual void oscReceive(ofxOscMessage &m);

	void setupBasis(trackingManager* tPtr,paramBox* pbPtr);
	void updateBasis();
	void drawBasis();

	paramBox*			pBoxPtr;
	trackingManager*	trackPtr;

	bool				bEnable;
	string				sceneName;
};

#endif /* defined(__natnetTracker__trackerBaseScene__) */
