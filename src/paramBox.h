//
//  paramBox.h
//  natnetTracker
//
//  Created by Ovis aries on 2014/08/26.
//
//

#ifndef natnetTracker_paramBox_h
#define natnetTracker_paramBox_h

#include "ofMain.h"

struct paramBox{
	float car_width;
	float car_height;
	float volume_gain;

	vector <float> *audio_l;
	vector <float> *audio_r;
	vector <float> *audio_v;
};

#endif
