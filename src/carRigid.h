//
//  carRigid.h
//  natnetTracker
//
//  Created by Ovis aries on 2014/08/25.
//
//

#ifndef natnetTracker_carRigid_h
#define natnetTracker_carRigid_h

#include "ofMain.h"

class carRigid{
public:

	carRigid(int ID, ofMatrix4x4 mt){
		mat = mt;
		id_ = ID;
		node.setTransformMatrix(mat);
		isAlive = true;
		aliveFrame = 0;
	}

	ofMatrix4x4 mat;
	ofNode node;
	int id_;
	int aliveFrame;
	bool isAlive;

	ofVec3f vector;//TODO: 速度と回転速度計算する
	float	angleVec;

	void update(){

		aliveFrame++;
		if (aliveFrame > 120) isAlive = false;

	}
	void draw(){
		node.draw();
	}

	void setMatrix(ofMatrix4x4 mt,float scale){
		mat = mt;
		node.setTransformMatrix(mat);
		node.setGlobalPosition(node.getGlobalPosition()*scale + ofVec3f(255,0,255));
		node.rotate(60, 0.0, 1.0, 0.0);
		aliveFrame = 0;
	}

	ofNode getHomographyPosition(){
		ofNode n;
		n = node;
//		n.setTransformMatrix(<#const ofMatrix4x4 &m44#>)
	}
	
};

#endif
