#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	sceneMan.setup();

	uiCanvas.addLabel("Console",OFX_UI_FONT_LARGE);
	uiCanvas.addSpacer();
	uiCanvas.addToggle("gohst_circle", &sceneMan.viewCircleTrack);
	uiCanvas.addToggle("gridMarker", &sceneMan.viewTestPattern);
	uiCanvas.addToggle("CheckBoard", &sceneMan.checkBoard);

	uiCanvas.addSlider("car_W", 0.0, 300.0, &sceneMan.pBox.car_width);
	uiCanvas.addSlider("car_H", 0.0, 300.0, &sceneMan.pBox.car_height);
	uiCanvas.addSlider("translate_scale", 0.0, 400.0, &sceneMan.tracker.translate_scale);

	uiCanvas.addSpacer();

	for (int i = 0;i < sceneMan.scenes.size();i++){
		uiCanvas.addToggle(sceneMan.scenes[i]->sceneName,
						   &sceneMan.scenes[i]->bEnable);
	}

	uiCanvas.autoSizeToFitWidgets();
	uiCanvas.setup();

	/*======Audio Stream Setup===========*/
	soundStream.listDevices();
	int bufferSize = 256;
	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
	sceneMan.pBox.audio_l = &left;
	sceneMan.pBox.audio_r = &right;
	sceneMan.pBox.audio_v = &vol_buf;
	/*======Audio Stream Setup===========*/
}

//--------------------------------------------------------------
void ofApp::update(){
	sceneMan.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(25);

	sceneMan.draw();
	sceneMan.masterBuf.draw(1920,0);
}

void ofApp::audioIn(float *input, int bufferSize, int nChannels){

	float vol_t = 0.0;
	for (int i = 0;i < bufferSize;i++){
		left[i]		= input[i*2]*0.5 * sceneMan.pBox.volume_gain;
		right[i]	= input[i*2+1]*0.5 * sceneMan.pBox.volume_gain;
		vol_t += left[i] * left[i];
		vol_t += right[i] * right[i];
	}

	vol_buf.push_back(vol_t);
	if (vol_buf.size() > 500){
		vol_buf.erase(vol_buf.begin());
	}
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'f') ofToggleFullscreen();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
