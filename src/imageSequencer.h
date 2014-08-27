//
//  imageSequencer.h
//  natnetTracker
//
//  Created by Ovis aries on 2014/08/26.
//
//

#ifndef __natnetTracker__imageSequencer__
#define __natnetTracker__imageSequencer__

#include "ofMain.h"

enum imageSequence_type{
	SEQ_TYPE_IMAGE,
	SEQ_TYPE_CIECLE1,
	SEQ_TYPE_ANGLE1
};

class imageSequencer{
public:
	void setup(imageSequence_type type);
	void setImage(vector<string> files);
	void play(ofVec2f pos_, float ang);
	void reset();
	void draw();
	void drawSequencial();

	ofVec2f				pos;
	float				angle;
	bool				isPlay;
	int					currentFrame;

	imageSequence_type	currentType;
	vector<ofImage>		images;

	float sigmoid(float x,bool flip = false){
		x = (x - 0.5) * 12.0;
		float e = 2.71828182846;

		if (!flip) return 1.0 / (1.0 + pow(e,-x));
		else	   return 1.0 - (1.0 / (1.0 + pow(e, -x)));
	}

	float hue;
};

#endif /* defined(__natnetTracker__imageSequencer__) */
