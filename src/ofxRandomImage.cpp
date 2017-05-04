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
			cout << "successfully loaded api " << api->getName() << endl;
		}else {
			cout << "could not load " << api->getName() << endl;
		}
	}

}

void ofxRandomImage::update(ofEventArgs &e){
	if(rimg.waiting && rimg.url != ""){
		rimg.waiting = false;
		rimg.loading = true;
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
		cout << response.status << " " << response.error << " for request " << response.request.name << endl;
		if(response.status!=-1) rimg.loading=false;
		ofRemoveURLRequest(response.request.getId());
	}
}

void ofxRandomImage::loadRandomImage(ofImage& image){

	cout << "ofxRandomImage::loadRandomImage" << endl;

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

