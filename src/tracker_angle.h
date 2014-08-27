//
//  tracker_angle.h
//  natnetTracker
//
//  Created by Ovis aries on 2014/08/27.
//
//

#ifndef __natnetTracker__tracker_angle__
#define __natnetTracker__tracker_angle__

#include "tracker_sequence.h"

class tracker_angle : public tracker_sequence{
public:
	virtual void setup();
	virtual void update();
	virtual void draw();
	virtual void oscReceive(ofxOscMessage &m);

	void play(int seqNum);
	
};

#endif /* defined(__natnetTracker__tracker_angle__) */
