//
//  trail_singleClass.h
//  natnetTracker
//
//  Created by Ovis aries on 2014/08/27.
//
//

#ifndef natnetTracker_trail_singleClass_h
#define natnetTracker_trail_singleClass_h

#include "ofMain.h"

class singleTrail{
public:

	singleTrail(ofVec3f defPt){
		pts.push_back(ofVec3f(defPt));
		aliveCount = 0;
	}

	virtual void update(){
		while (pts.size() > 50){
			pts.erase(pts.begin());
		}

		for (int i = 0;i < pts.size() - 1;i++){
			pts[i] += (pts[i+1] - pts[i]) / 25.0;
		}

		aliveCount++;
	}

	virtual void draw(){
		ofEnableBlendMode(OF_BLENDMODE_ADD);
		ofSetColor(255,70,70);
		glBegin(GL_TRIANGLE_STRIP);
		for (int i = 0;i < pts.size();i++){
			glVertex3f(pts[i].x+(ofNoise(i*3.4)-0.5)*70.0,
					   pts[i].y+(ofNoise(i*7.3)-0.5)*70.0,
					   pts[i].z+(ofNoise(i*5.2)-0.5)*70.0);
		}
		glEnd();
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
		ofSetColor(255);
	}

	virtual void addPt(ofVec3f p){
		if ((pts.size() < 2) ||
			(p.distanceSquared(pts.back()) > 5)){
			aliveCount = 0;
			pts.push_back(ofVec3f(p));
		}
	}

	int aliveCount;
	vector<ofVec3f> pts;

};

class scopeTrail : public singleTrail{
public:

	scopeTrail(ofVec3f defPt, vector<float> *ptr) : singleTrail(defPt){
		scopePtr = ptr;
	};

	void update(){
		aliveCount++;
	}

	virtual void draw(){
		ofEnableBlendMode(OF_BLENDMODE_ADD);
		ofSetColor(20,200,150);
		if (pts.size() > 2){
			glLineWidth(3.0);
			glBegin(GL_LINES);

			for (int i = 0;i < pts.size() - 1;i++){
				ofVec3f cent = pts[i];
				ofVec3f axis = pts[i] - pts[i+1];
				axis.rotate(90,ofVec3f(0.0,1.0,0.0));
				axis.normalize();

				int idx = scopePtr->size() * float(i) / (float)pts.size();
				ofVec3f t1 = cent + axis * (*scopePtr)[idx] * 300.0;
				ofVec3f t2 = cent - axis * (*scopePtr)[idx] * 300.0;
				glVertex3d(t1.x, t1.y, t1.z);
				glVertex3d(t2.x, t2.y, t2.z);
			}

			glEnd();
			glLineWidth(1.0);
		}
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
		ofSetColor(255);
	}

	vector<float> *scopePtr;
};

class audioTrail : public singleTrail{
public:

	audioTrail(ofVec3f defPt, float* VolumePtr) : singleTrail(defPt){
		VPtr = VolumePtr;
		pts.push_back(ofVec3f(defPt));
		aliveCount = 0;
	}

	virtual void draw(){
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, &audioPts[0]);

		glDrawArrays(GL_LINE_STRIP, 0, audioPts.size());

		glDisableClientState(GL_VERTEX_ARRAY);
	}

	virtual void addPt(ofVec3f p){
		aliveCount = 0;
		pts.push_back(ofVec3f(p));

		if (pts.size() > 1){
			ofVec3f before = pts[pts.size()-2];
			ofVec3f back = pts.back();

			ofVec3f axis = before - back;
			axis.rotate(90, ofVec3f(0.0, 1.0, 0.0));
			axis.normalize();

			audioPts.push_back(pts.back() + axis * *VPtr * 10.0);
			audioPts.push_back(pts.back() - axis * *VPtr * 10.0);
		}
	}

	vector<ofVec3f> audioPts;
	float *VPtr;
};

class aSTrail : public audioTrail{
public:
	aSTrail(ofVec3f defPt, float* VolPt, vector<float> *scp) : audioTrail(defPt, VolPt){
		Scope = scp;
	}

	virtual void draw(){

		glLineWidth(7.0);
		ofEnableBlendMode(OF_BLENDMODE_ADD);
		ofSetColor(130,130,255);
		glBegin(GL_LINES);

		for (int i = 0;i < audioPts.size();i++){
			int idx = Scope->size() * float(i) / (float)audioPts.size();

			ofVec3f gain = audioPts[i] * (*Scope)[idx] * 30.0;
			gain.limit(140.0);

			ofVec3f v  = basePts[i] + gain;
			ofVec3f v2 = basePts[i] - gain;
			glVertex3f(v.x,v.y,v.z);
			glVertex3f(v2.x,v2.y,v2.z);
		}

		glEnd();
		ofSetColor(255);
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
		glLineWidth(1.0);
	}

	virtual void addPt(ofVec3f p){

		if ((pts.size() < 2) ||
			(p.distanceSquared(pts.back()) > 5)){
			aliveCount = 0;
			pts.push_back(ofVec3f(p));
		}

		if (pts.size() > 1){
			ofVec3f before = pts[pts.size()-2];
			ofVec3f back = pts.back();

			ofVec3f axis = before - back;
			axis.rotate(90, ofVec3f(0.0, 0.0, 1.0));
			axis.normalize();

			audioPts.push_back(  axis * *VPtr * 10.0);
			audioPts.push_back(- axis * *VPtr * 10.0);

			basePts.push_back(pts.back());
			basePts.push_back(pts.back());
		}
	}
	
	vector<ofVec3f> basePts;
	vector<float>* Scope;
};

#endif
