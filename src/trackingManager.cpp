//
//  trackingManager.cpp
//  natnetTracker
//
//  Created by Ovis aries on 2014/08/25.
//
//

#include "trackingManager.h"

void trackingManager::setup(ofFbo* outBuf){

    natnet.setup("en3", "169.254.174.129");

	outputBuf = outBuf;
	baseMap.allocate(512, 512);
	translate_scale = 100.0;
	translate_offset.set(-2,-2);

	srcPt.assign(4, ofVec2f(0,0));
	dstPt.assign(4, ofVec2f(0,0));

	homoPts.push_back(homoGraphPoint(ofVec2f(0,0),
									 ofVec2f(0,0)));

	homoPts.push_back(homoGraphPoint(ofVec2f(512,0),
									 ofVec2f(1920,0)));

	homoPts.push_back(homoGraphPoint(ofVec2f(0,512),
									 ofVec2f(0,1080)));

	homoPts.push_back(homoGraphPoint(ofVec2f(512,512),
									 ofVec2f(1920,1080)));

	src_scale = 1.0;
	dst_scale = 0.5;

	src_offset.set(250,0);
	dst_offset.set(250,520);

	homoPtCatched = false;
	homoPtCisSrc = false;
	ofAddListener(ofEvents().mousePressed, this, &trackingManager::mousePressed);
	ofAddListener(ofEvents().mouseDragged, this, &trackingManager::mouseDragged);
	ofAddListener(ofEvents().mouseReleased, this, &trackingManager::mouseReleased);

	genHomography();
	
}

void trackingManager::update(){
	//carRigid processing ==================================
	for (int i = 0;i < cars.size();i++){

		cars[i].update();
		if (!cars[i].isAlive) cars.erase(cars.begin()+i);

	}

	//Natnet processing ==================================
	natnet.update();
	for (int i = 0;i < natnet.getNumRigidBody();i++){
		ofxNatNet::RigidBody r = natnet.getRigidBodyAt(i);
		setRigid(r);
	}

}

void trackingManager::draw(){
	baseMap.begin();
	ofClear(0, 30, 50, 255);

	ofSetColor(50);
	for (int i = 0;i < 512;i+=16){
		ofLine(0, i, 512, i);
		ofLine(i, 0, i, 512);
	}

	ofPushMatrix();
	ofSetColor(255);
	for (int i = 0;i < cars.size();i++){
		ofPushMatrix();
		ofTranslate(cars[i].node.getGlobalPosition().x,
					cars[i].node.getGlobalPosition().z,0);
		ofLine(-5, 0, 5, 0);
		ofLine(0, -5, 0, 5);
		ofPopMatrix();
	}

	ofPopMatrix();
	baseMap.end();


	//ソースビューの描画
	drawDebugView();
}

void trackingManager::setRigid(ofxNatNet::RigidBody& rig){

	int existIdx = -1;

	for (int i = 0;i < cars.size();i++){
		if (cars[i].id_ == rig.id) existIdx = i;
	}

	if (existIdx != -1) cars[existIdx].setMatrix(rig.matrix,translate_scale);
	else				cars.push_back(carRigid(rig.id, rig.matrix));
	
}

ofVec2f trackingManager::getTrackPos(int Num){
	if (cars.size() == 0) return ofVec2f(0,0);

	Num = ofClamp(Num, 0, getNumCars() - 1);

	ofVec2f src = ofVec2f(cars[Num].node.getGlobalPosition().x,
						  cars[Num].node.getGlobalPosition().z);

	ofVec2f dst;
	double A = homography.at<double>(0,0);
	double B = homography.at<double>(0,1);
	double C = homography.at<double>(0,2);
	double D = homography.at<double>(1,0);
	double E = homography.at<double>(1,1);
	double F = homography.at<double>(1,2);
	double G = homography.at<double>(2,0);
	double H = homography.at<double>(2,1);

	dst.x = (src.x * A + src.y * B + C) / (src.x * G + src.y * H + 1);
	dst.y = (src.x * D + src.y * E + F) / (src.x * G + src.y * H + 1);

	return dst;
}

float trackingManager::getTrackRotate(int Num){
	if (cars.size() == 0) return 0.f;
	Num = ofClamp(Num, 0, getNumCars() - 1);

	float rotate = cars[Num].node.getOrientationQuat().getEuler().y;
	return rotate;
}

void trackingManager::drawDebugView(){

	ofSetColor(255);

	ofPushMatrix();
	ofTranslate(src_offset);
	glScalef(src_scale, src_scale, 1.0);
	baseMap.draw(0,0);
	ofPopMatrix();

	ofPushMatrix();
	ofTranslate(dst_offset);
	glScalef(dst_scale, dst_scale, 1.0);
	outputBuf->draw(0,0);
	ofPopMatrix();

	ofColor src_color = ofColor(255, 100, 0);
	ofColor dst_color = ofColor(0, 100, 255);

	for (int i = 0;i < homoPts.size();i++){
		ofVec2f src,dst;
		src = homoPts[i].src * src_scale + src_offset;
		dst = homoPts[i].dst * dst_scale + dst_offset;

		ofNoFill();
		ofSetColor(src_color);
		ofCircle(src, 10);
		ofSetColor(dst_color);
		ofCircle(dst, 10);

		ofFill();
		ofSetColor(src_color);
		ofCircle(src, 3);
		ofSetColor(dst_color);
		ofCircle(dst, 3);

		ofSetColor(128);
		ofLine(src, dst);
	}
}

void trackingManager::mousePressed(ofMouseEventArgs &arg){

	for (int i = 0;i < homoPts.size();i++){
		ofVec2f src,dst;
		src = homoPts[i].src * src_scale + src_offset;
		dst = homoPts[i].dst * dst_scale + dst_offset;

		if (src.distanceSquared(arg) < 100){
			homoPtCatched = true;
			homoPtCisSrc = true;
			homoPtIndex = i;
		}
		if (dst.distanceSquared(arg) < 100){
			homoPtCatched = true;
			homoPtCisSrc = false;
			homoPtIndex = i;
		}
	}

}

void trackingManager::mouseDragged(ofMouseEventArgs &arg){
	if (homoPtCatched){

		if (homoPtCisSrc)	homoPts[homoPtIndex].src = (arg - src_offset) / src_scale;
		else				homoPts[homoPtIndex].dst = (arg - dst_offset) / dst_scale;

		genHomography();
	}
}

void trackingManager::mouseReleased(ofMouseEventArgs &arg){
	homoPtCatched = false;
	homoPtCisSrc = false;

	genHomography();
}

void trackingManager::genHomography(){
	//generate homography ================================
	vector<ofxCv::Point2f> srcPoints, dstPoints;
	for (int i = 0;i < homoPts.size();i++){
		srcPoints.push_back(ofxCv::Point2f(homoPts[i].src.x,
										   homoPts[i].src.y));
		dstPoints.push_back(ofxCv::Point2f(homoPts[i].dst.x,
										   homoPts[i].dst.y));
	}

	homography = ofxCv::findHomography(ofxCv::Mat(srcPoints),
									   ofxCv::Mat(dstPoints));
}
