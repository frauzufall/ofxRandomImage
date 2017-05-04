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
		cout << "setting up flickr api with key " << key << endl;
		this->key = key;
		active.set(true);
		std::string newest_image_query = "https://api.flickr.com/services/rest/?method=flickr.photos.getRecent&api_key=" + key + "&per_page=1";
		cout << "ofxRandomImageFlickr newest image: " << newest_image_query << endl;
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

	cout << "ofxRandomImageFlickr::setRandomImageUrl" << endl;

	this->url = &url;
	url = "";

	if(maxId == 0){
		cout << "ofxRandomImageFlickr::setRandomImageUrl waiting for maxId" << endl;
		urlWaiting = true;
		return;
	}

	int id = ofRandom(maxId);

	std::string random_image_query = "https://api.flickr.com/services/rest/?method=flickr.photos.getInfo&photo_id="
			+ ofToString(id) + "&api_key=" + key;

	cout << "loading random flickr image: " << random_image_query << endl;

	ofLoadURLAsync(random_image_query, "flickr_random_image");

}

void ofxRandomImageFlickr::urlResponse(ofHttpResponse & response){
	if(response.status==200){
		if(response.request.name == "flickr_newest_image"){

			cout << "flickr_newest_image: " << response.data << endl;

			ofXml xml;
			if(xml.load(response.data)){
				xml = xml.findFirst("rsp/photos/photo");
				if(xml){
					maxId = xml.getAttribute("id").getIntValue();
					cout << "ofxRandomImageFlickr got maxId "  << maxId << endl;
				}else {
					cout << "could not read newest photo" << endl;
				}

				if(urlWaiting){
					urlWaiting = false;
					setRandomImageUrl(*url);
				}
			}else{
				cout << "could not read newest photo rest response " << endl;
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
		cout << response.status << " " << response.error << " for request " << response.request.name << endl;
		if(response.status!=-1) {

		}
		ofRemoveURLRequest(response.request.getId());
	}
}
