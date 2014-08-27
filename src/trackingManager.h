//
//  trackingManager.h
//  natnetTracker
//
//  Created by Ovis aries on 2014/08/25.
//
//

#ifndef __natnetTracker__trackingManager__
#define __natnetTracker__trackingManager__

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxNatNet.h"
#include "ofxAssimpModelLoader.h"
#include "carRigid.h"
#include "ofxCv.h"

class homoGraphPoint{
public:
	homoGraphPoint(ofVec2f s,ofVec2f d){
		src = s;
		dst = d;
	}

	ofVec2f src;
	ofVec2f dst;
};

class trackingManager{
public:
	void setup(ofFbo* outBuf);
	void update();
	void draw();

	void setRigid(ofxNatNet::RigidBody& rig);

	int getNumCars(){return cars.size();};
	ofVec2f getTrackPos(int Num);
	float	getTrackRotate(int Num);

	void drawDebugView();
	void genHomography();

	ofxNatNet			natnet;
	vector<carRigid>	cars;

	ofFbo				baseMap;
	ofFbo*				outputBuf;
	cv::Mat				homography;
	vector<ofVec2f>		srcPt,dstPt;
	vector<homoGraphPoint> homoPts;
	float				translate_scale;
	ofVec2f				translate_offset;

	float				src_scale,dst_scale;
	ofVec2f				src_offset,dst_offset;

	bool				homoPtCatched;
	bool				homoPtCisSrc;
	int					homoPtIndex;
	void				mousePressed(ofMouseEventArgs &arg);
	void				mouseDragged(ofMouseEventArgs &arg);
	void				mouseReleased(ofMouseEventArgs &arg);
};

#endif /* defined(__natnetTracker__trackingManager__) */
