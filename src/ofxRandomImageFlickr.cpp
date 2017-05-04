#include "ofxRandomImageFlickr.h"

ofxRandomImageFlickr::ofxRandomImageFlickr(){
	ofRegisterURLNotification(this);
}

ofxRandomImageFlickr::~ofxRandomImageFlickr(){
	ofUnregisterURLNotification(this);
	maxId = 0;
	urlWaiting = false;
}

std::string ofxRandomImageFlickr::getName(){
	return "flickr";
}

void ofxRandomImageFlickr::setup(std::string key){
	if(key != ""){
		ofLogVerbose("ofxRandomImageFlickr") << "setup: flickr API key " << key << ".";
		this->key = key;
		active.set(true);
		std::string newest_image_query = "https://api.flickr.com/services/rest/?method=flickr.photos.getRecent&api_key=" + key + "&per_page=1";
		ofLoadURLAsync(newest_image_query, "flickr_newest_image");
	}
}

bool ofxRandomImageFlickr::loadFromXml(const ofXml& xml){
	ofXml xmlkey = xml.findFirst("apikeys/flickr");
	if(xmlkey){
		std::string _key = xmlkey.getValue();
		setup(_key);
	}
	return key != "";
}

void ofxRandomImageFlickr::setRandomImageUrl(std::string& url){

	this->url = &url;
	url = "";

	if(maxId == 0){
		ofLogWarning("ofxRandomImageFlickr") << "setRandomImageUrl: cannot load random image while waiting for maxId.";
		urlWaiting = true;
		return;
	}

	int id = ofRandom(maxId);

	std::string random_image_query = "https://api.flickr.com/services/rest/?method=flickr.photos.getInfo&photo_id="
			+ ofToString(id) + "&api_key=" + key;

	ofLogVerbose("ofxRandomImageFlickr") << "setRandomImageUrl: trying to load image with id " << id << "(query: " << random_image_query << ").";

	ofLoadURLAsync(random_image_query, "flickr_random_image");

}

void ofxRandomImageFlickr::urlResponse(ofHttpResponse & response){
	if(response.status==200){
		if(response.request.name == "flickr_newest_image"){

			ofXml xml;
			if(xml.load(response.data)){
				xml = xml.findFirst("rsp/photos/photo");
				if(xml){
					maxId = xml.getAttribute("id").getIntValue();
					ofLogVerbose("ofxRandomImageFlickr") << "urlResponse: got maxId " << maxId;
				}else {
					ofLogError("ofxRandomImageFlickr") << "urlResponse: could not read newest photo.";
				}

				if(urlWaiting){
					urlWaiting = false;
					setRandomImageUrl(*url);
				}
			}else{
				ofLogError("ofxRandomImageFlickr") << "urlResponse: could not read newest photo rest response.";
			}

		}
		if(response.request.name == "flickr_random_image"){

			ofXml xml;
			xml.load(response.data);
			ofXml photo = xml.findFirst("rsp/photo");
			if(photo){
				std::string id = photo.getAttribute("id").getValue();
				std::string secret = photo.getAttribute("secret").getValue();
				std::string server = photo.getAttribute("server").getValue();
				std::string farm = photo.getAttribute("farm").getValue();
				*this->url = "https://farm"
					 + farm + ".staticflickr.com/"
					 + server + "/" + id + "_" + secret + ".jpg";
			}else {
				setRandomImageUrl(*url);
			}

		}
	}else{
		ofLogVerbose("ofxRandomImageFlickr") << "urlResponse: " << response.status << " " << response.error << " for request " << response.request.name;
		if(response.status!=-1) {

		}
		ofRemoveURLRequest(response.request.getId());
	}
}
