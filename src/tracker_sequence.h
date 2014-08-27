//
//  tracker_sequence.h
//  natnetTracker
//
//  Created by Ovis aries on 2014/08/26.
//
//

#ifndef __natnetTracker__tracker_sequence__
#define __natnetTracker__tracker_sequence__

#include "trackerBaseScene.h"
#include "imageSequencer.h"

#define SEQ_DUPLICATE 10

class tracker_sequence : public trackerBaseScene{
public:
	virtual void setup();
	virtual void update();
	virtual void draw();
	virtual void oscReceive(ofxOscMessage &m);

	virtual void play(int seqNum);

	vector<imageSequencer> seqs[SEQ_DUPLICATE];
	imageSequencer testSeq;
};

#endif /* defined(__natnetTracker__tracker_sequence__) */
