//
//  tracker_sequence.cpp
//  natnetTracker
//
//  Created by Ovis aries on 2014/08/26.
//
//

#include "tracker_sequence.h"

void tracker_sequence::setup(){
	sceneName = "trackerSeq";

	for (int i = 0;i < SEQ_DUPLICATE;i++){

		//シーケンサの追加
		seqs[i].push_back(imageSequencer());
		seqs[i].back().setup(SEQ_TYPE_CIECLE1);

	}
}

void tracker_sequence::update(){

	static bool pushSW = false;
	if (ofGetKeyPressed('a') && !pushSW){
		play(0);
		pushSW = true;
	}else if (!ofGetKeyPressed('a')){
		pushSW = false;
	}
}

void tracker_sequence::draw(){

	for (int j = 0; j < SEQ_DUPLICATE;j++){
		for (int i = 0;i < seqs[j].size();i++){
			seqs[j][i].draw();
		}
	}

}

void tracker_sequence::oscReceive(ofxOscMessage &m){

	if (m.getAddress() == "/beat/"){
		play(0);
	}

}

void tracker_sequence::play(int seqNum){

	bool breaker = false;

	for (int o = 0;o < trackPtr->getNumCars();o++){
		breaker = false;

		for (int j = 0; j < SEQ_DUPLICATE;j++){
			if (!seqs[j][seqNum].isPlay && !breaker){
				seqs[j][seqNum].play(trackPtr->getTrackPos(o),
									 trackPtr->getTrackRotate(o));
				breaker = true;
			}
		}

	}

}