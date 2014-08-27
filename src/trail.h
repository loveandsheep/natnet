//
//  trail.h
//  natnetTracker
//
//  Created by Ovis aries on 2014/08/27.
//
//

#ifndef __natnetTracker__trail__
#define __natnetTracker__trail__

#include "trackerBaseScene.h"
#include "trail_singleClass.h"

class trail : public trackerBaseScene{
public:
	virtual void setup();
	virtual void update();
	virtual void draw();
	virtual void oscReceive(ofxOscMessage &m);

	void setPoint(ofVec2f pt);

	float audioFloat;
	vector<float>*scope_left;
	
	vector<aSTrail> trails;
};

#endif /* defined(__natnetTracker__trail__) */
