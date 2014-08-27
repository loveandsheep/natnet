//
//  imageSequencer.cpp
//  natnetTracker
//
//  Created by Ovis aries on 2014/08/26.
//
//

#include "imageSequencer.h"

void imageSequencer::setup(imageSequence_type type){

	currentType = type;
	currentFrame = 0;
	images.clear();
	isPlay = false;
	
}

void imageSequencer::setImage(vector<string> files){
	for (int i = 0;i < files.size();i++){
		images.push_back(ofImage(files[i]));
	}
}

void imageSequencer::play(ofVec2f pos_, float ang){
	reset();
	isPlay	= true;
	pos		= pos_;
	angle	= ang;
}

void imageSequencer::draw(){
	if (isPlay){

		ofPushMatrix();
		ofTranslate(pos);
		ofRotateZ(-angle);

		ofColor c;
		c.setHsb(hue, 255, 255);
		ofSetColor(c);

		drawSequencial();

		ofPopMatrix();
		currentFrame++;

		if (currentFrame > 30) reset();
	}
}

void imageSequencer::reset(){
	isPlay = false;
	currentFrame = 0;
}

void imageSequencer::drawSequencial(){

	//テスト
	if (currentType == SEQ_TYPE_CIECLE1){
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofRect(0, 0,
			   pow(currentFrame / 30.0,1.0/4.0) * 100.0,
			   pow(currentFrame / 30.0,1.0/4.0) * 100.0);
		ofSetRectMode(OF_RECTMODE_CORNER);

		ofSetColor(hue+30, 255, 255);
		ofLine(0,-100, 0, 100);
	}

	if (currentType == SEQ_TYPE_ANGLE1){
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofRect(0, 600.0 - pow(currentFrame / 30.0,1.0/4.0) * 600.0,
			   pow(currentFrame / 30.0,1.0/4.0) * 100.0,
			   pow(currentFrame / 30.0,1.0/4.0) * 100.0);
		ofSetRectMode(OF_RECTMODE_CORNER);
	}

}