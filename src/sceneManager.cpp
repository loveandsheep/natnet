//
//  sceneManager.cpp
//  natnetTracker
//
//  Created by Ovis aries on 2014/08/25.
//
//

#include "sceneManager.h"

void sceneManager::setup(){

	receiver.setup(12400);
	masterBuf.allocate(1920,1080);

	tracker.setup(&masterBuf);

	viewTestPattern = false;
	pBox.car_width = 100.0;
	pBox.car_height = 100.0;
	pBox.volume_gain = 1.0;

	scenes.push_back(new trackerBaseScene());
	scenes.push_back(new tracker_sequence());
	scenes.push_back(new tracker_angle());
	scenes.push_back(new trail());

	for (int i = 0;i < scenes.size();i++){
		scenes[i]->setupBasis(&tracker,&pBox);
		scenes[i]->setup();
	}

}

void sceneManager::update(){

	debugFunc();
	tracker.update();

	for (int i = 0;i < scenes.size();i++){
		if (scenes[i]->bEnable){
			scenes[i]->updateBasis();
			scenes[i]->update();
		}
	}

	while (receiver.hasWaitingMessages()){
		ofxOscMessage m;
		receiver.getNextMessage(&m);

		for (int i = 0;i < scenes.size();i++)
			if (scenes[i]->bEnable) scenes[i]->oscReceive(m);
	}

}

void sceneManager::draw(){
	tracker.draw();

	masterBuf.begin();
	ofClear(0, 0, 0, 255);

	if (checkBoard){
		ofSetColor(255);
		int cnt = 0;
		for (int i = 0;i < 1920;i+=100){
			for (int j = 0;j < 1080;j+=100){
				cnt++;
				ofColor c;
				c.setHsb(((cnt*150)%255), 70, 255);
				ofSetColor(c);
				ofRect(i, j, 100, 100);
			}
		}
	}

	for (int i = 0;i < scenes.size();i++){
		if (scenes[i]->bEnable){
			scenes[i]->drawBasis();
			scenes[i]->draw();
		}
	}

	masterBuf.end();
}

void sceneManager::debugFunc(){
	//for Debugigng
	if (ofGetKeyPressed(' ')){
		ofMatrix4x4 mt;
		mt.rotate(ofGetMouseX(), 0.0, 1.0, 0.0);
		mt.setTranslation((ofGetMouseX() - ofGetWidth()/2.0)/200.0,
						  0.0,
						  (ofGetMouseY() - ofGetHeight()/2.0)/200.0);

		ofxNatNet::RigidBody r;
		r.id = 2;
		r.matrix = mt;
		tracker.setRigid(r);
	}

	if (viewCircleTrack){
		static float angle = 0.0;
		angle += 2;
		ofMatrix4x4 mt;
		mt.rotate(-angle-90, 0.0, 1.0, 0.0);
		mt.setTranslation(cos(ofDegToRad(angle))*1.0, 0.0,
						  sin(ofDegToRad(angle))*1.0);

		ofxNatNet::RigidBody r;
		r.id = 14;
		r.matrix = mt;
		tracker.setRigid(r);
	}

	if (viewTestPattern){
		int cnt = 0;
		for (int i = 0;i < 512;i+=50){
			for (int j = 0;j < 512;j+=50){
				ofMatrix4x4 mt;
				mt.setTranslation(i/200.0,0,j/200.0);

				cnt++;
				ofxNatNet::RigidBody r;
				r.id = cnt;
				r.matrix = mt;
				if (cnt != 2) tracker.setRigid(r);

			}
		}
	}
}