#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetFrameRate(120);
	ofSetLogLevel(OF_LOG_VERBOSE);

	// if you don't want to use pointers and vectors, you can just do this:
	// ofImage img;
	// randomImage.loadRandomImage(img);

	randomImage.setup();
	ofPtr<ofImage> img(new ofImage());
	randomImage.loadRandomImage(*img.get());

	imgs.push_back(img);

}

//--------------------------------------------------------------
void ofApp::update() {

}


//--------------------------------------------------------------
void ofApp::draw(){

	ofBackgroundGradient(ofColor::white, ofColor::gray);

	int rowcount = ceil(sqrt(imgs.size()));
	int width = min(ofGetWidth(), ofGetHeight())/rowcount;

	int i = 0;
	for(ofPtr<ofImage> img : imgs){
		if(img->isAllocated()){
			img->draw((i%rowcount)*width, (i/rowcount)*width, width, width);
		}
		i++;
	}

	ofFill();
	ofSetColor(0);
	ofDrawRectangle(10, 10, 400, 40);
	ofDrawRectangle(10, 60, 250, 40);
	ofSetColor(255);
	ofDrawBitmapString("press the spacebar to display a new random image", 20, 35);
	ofDrawBitmapString("press 'c' to clear the images", 20, 85);

	if(randomImage.isLoading()){
		ofFill();
		ofSetColor(255,0,0);
		ofDrawRectangle(10, 110, 100, 40);
		ofSetColor(255);
		ofDrawBitmapString("Loading...", 20, 135);
	}

}

//--------------------------------------------------------------
void ofApp::exit(){
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	if(key == ' '){
		ofPtr<ofImage> img(new ofImage());
		randomImage.loadRandomImage(*img.get());
		imgs.push_back(img);
	}
	if(key == 'c'){
		imgs.clear();
	}

}

//--------------------------------------------------------------
void ofApp::mouseMoved(ofMouseEventArgs &args){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(ofMouseEventArgs &args){
}

//--------------------------------------------------------------
void ofApp::mousePressed(ofMouseEventArgs &args){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(ofMouseEventArgs &args){
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
