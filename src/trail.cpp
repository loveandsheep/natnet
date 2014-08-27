//
//  trail.cpp
//  natnetTracker
//
//  Created by Ovis aries on 2014/08/27.
//
//

#include "trail.h"

void trail::setup(){
	trails.clear();

	sceneName = "trail";
}

void trail::update(){
	audioFloat = pBoxPtr->audio_v->back();

	for (int i = 0;i < trails.size();i++){
		trails[i].update();

		if (trails[i].aliveCount > 120)
			trails.erase(trails.begin()+i);

	}

	for (int i = 0;i < trackPtr->getNumCars();i++){
		setPoint(trackPtr->getTrackPos(i));
	}

	if (ofGetKeyPressed('c')) trails.clear();
}

void trail::draw(){
	if (trails.size() > 0){
		for (int i = 0;i < trails.size();i++){
			trails[i].draw();
		}
	}
}

void trail::oscReceive(ofxOscMessage &m){

}

void trail::setPoint(ofVec2f pt){
	int catchTrail = -1;

	for (int i = 0;i < trails.size();i++){
		if (trails[i].pts.back().distanceSquared(pt) < 10000){
			catchTrail = i;
		}
	}

	ofVec3f p = pt;
	p.z = 0;

	if (catchTrail != -1){
		trails[catchTrail].addPt(pt);
	}else{
		trails.push_back(aSTrail(pt, &audioFloat, pBoxPtr->audio_l));
	}
}