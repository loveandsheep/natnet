//
//  tracker_angle.cpp
//  natnetTracker
//
//  Created by Ovis aries on 2014/08/27.
//
//

#include "tracker_angle.h"


void tracker_angle::setup(){
	sceneName = "trackerAngle";

	for (int i = 0;i < SEQ_DUPLICATE;i++){

		//シーケンサの追加
		seqs[i].push_back(imageSequencer());
		seqs[i].back().setup(SEQ_TYPE_ANGLE1);

	}
}

void tracker_angle::update(){

	static bool pushSW = false;
	if (ofGetKeyPressed('a') && !pushSW){
		play(0);
		pushSW = true;
	}else if (!ofGetKeyPressed('a')){
		pushSW = false;
	}
}

void tracker_angle::draw(){


	for (int j = 0; j < SEQ_DUPLICATE;j++){
		for (int i = 0;i < seqs[j].size();i++){
			seqs[j][i].draw();
		}
	}

}

void tracker_angle::oscReceive(ofxOscMessage &m){

	if (m.getAddress() == "/beat/"){
		play(0);
	}

}

void tracker_angle::play(int seqNum){

	bool breaker = false;

	for (int o = 0;o < trackPtr->getNumCars();o++){
		breaker = false;

		for (int j = 0; j < SEQ_DUPLICATE;j++){
			if (!seqs[j][seqNum].isPlay && !breaker){

				ofVec2f v = trackPtr->getTrackPos(o);
				float angle = atan2(v.y - 540, v.x - 960);

				seqs[j][seqNum].play(ofVec2f(960,540),
									 ofRadToDeg(-angle)+90);
				breaker = true;
			}
		}
		
	}
	
}