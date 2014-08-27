//
//  trackerBaseScene.cpp
//  natnetTracker
//
//  Created by Ovis aries on 2014/08/26.
//
//

#include "trackerBaseScene.h"

void trackerBaseScene::setupBasis(trackingManager* tPtr,paramBox* pbPtr){
	trackPtr	= tPtr;
	pBoxPtr		= pbPtr;
	sceneName	= "baseScene";
}

void trackerBaseScene::updateBasis(){

}

void trackerBaseScene::drawBasis(){

}

//=============================== 以下継承用メソッド

void trackerBaseScene::setup(){

}

void trackerBaseScene::update(){

}

void trackerBaseScene::draw(){
	for (int i = 0;i < trackPtr->getNumCars();i++){
		ofPushMatrix();
		ofTranslate(trackPtr->getTrackPos(i));
		ofRotateZ(-trackPtr->getTrackRotate(i));
		ofSetColor(255);
		ofNoFill();
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofRect(0, 0, pBoxPtr->car_width, pBoxPtr->car_height);
		ofSetRectMode(OF_RECTMODE_CORNER);
		ofFill();
		ofLine(-10, 0, 10, 0);
		ofLine(0, -10, 0, 10);
		ofPopMatrix();
	}
}

void trackerBaseScene::oscReceive(ofxOscMessage &m){

}