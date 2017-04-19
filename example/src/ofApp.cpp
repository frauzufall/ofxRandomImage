#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetFrameRate(120);

	randomImage.setup();
	randomImage.loadRandomImage(img);

}

//--------------------------------------------------------------
void ofApp::update() {
}


//--------------------------------------------------------------
void ofApp::draw(){

	ofBackgroundGradient(ofColor::white, ofColor::gray);

	if(img.isAllocated()){
		img.draw(0,120);
	}

	ofDrawBitmapString("displaying " + randomImage.getCurrentmageUrl(),20, 50);
	ofDrawBitmapString("press the spacebar to display a new random image",20, 70);
	ofDrawBitmapString("[h] show/hide the mouse info",20, 90);

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
		img.clear();
		randomImage.loadRandomImage(img);
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
