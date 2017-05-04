#include "ofAppRunner.h"
#include "ofxRandomImage.h"
#include "ofxRandomImageFlickr.h"
#include "RandomPersonalPictureFinder.h"
#include <regex>

ofxRandomImage::ofxRandomImage(){
	apis.clear();
	apis.push_back(new ofxRandomImageFlickr());
	setupdone = false;
}

ofxRandomImage::~ofxRandomImage(){
	if(setupdone){
		ofUnregisterURLNotification(this);
		ofRemoveListener(ofEvents().update, this, &ofxRandomImage::update);
	}
}

void ofxRandomImage::setup(){

	setupdone = true;

	ofRegisterURLNotification(this);
	ofAddListener(ofEvents().update, this, &ofxRandomImage::update);

	ofXml api_keys;
	api_keys.load("apikeys.xml");

	for(ofxRandomImageAPI* api : apis){
		if(api->loadFromXml(api_keys)){
			ofLogVerbose("ofxRandomImage") << "setup: successfully loaded API " << api->getName() << ".";
		}else {
			ofLogVerbose("ofxRandomImage") << "setup: could not load API " << api->getName() << ". Maybe the key is missing? Check bin/data/apikeys.xml.";
		}
	}

}

void ofxRandomImage::update(ofEventArgs &e){
	if(rimg.waiting && rimg.url != ""){
		rimg.waiting = false;
		rimg.loading = true;
		ofLogNotice("ofxRandomImage") << "update: the next random image URL is " << rimg.url;
		ofLoadURLAsync(rimg.url, "random_image");
	}
}

void ofxRandomImage::urlResponse(ofHttpResponse & response){
	if(response.status==200){
		if(response.request.name == "random_image"){
			rimg.img->load(response.data);
			rimg.loading=false;
		}
	}else{
		ofLogVerbose("ofxRandomImage") << "urlResponse: " << response.status << " " << response.error << " for request " << response.request.name;
		if(response.status!=-1) rimg.loading=false;
		ofRemoveURLRequest(response.request.getId());
	}
}

void ofxRandomImage::loadRandomImage(ofImage& image){

	rimg.img = &image;
	rimg.waiting = true;

	std::string url = "";
	std::string id = "";

//	switch(method){
//		case 0: {
//			string term = "openframeworks";
//			int page = 1;
//			url = "http://www.google.com/search?q="+term+"&tbm=isch&sout=1&tbs=isz&&start="+ofToString(page);
//			id = "random_google_search";
//			break;
//		}
//		case 1: {
//			url = RandomPersonalPictureFinder::generateFileName();
//			cout << url << endl;
//			id = "random_google_search";
//			break;
//		}
//	}

	apis.at(0)->setRandomImageUrl(rimg.url);

}

std::string ofxRandomImage::getCurrentmageUrl(){
	return rimg.url;
}

bool ofxRandomImage::isLoading(){
	return rimg.waiting || rimg.loading;
}
