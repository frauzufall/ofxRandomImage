#include "ofxRandomImage.h"
#include "RandomPersonalPictureFinder.h"
#include "ofxXmlPoco.h"
#include <regex>

ofxRandomImage::ofxRandomImage(){
	ofRegisterURLNotification(this);
}

ofxRandomImage::~ofxRandomImage(){
	ofUnregisterURLNotification(this);
}

void ofxRandomImage::setup(){

}

void ofxRandomImage::urlResponse(ofHttpResponse & response){
	if(response.status==200){
		if(response.request.name == "random_google_search"){
			std::string url = parseFromGoogle(response.data);
			this->rimg.url = url;
			cout << "load random image with url " << url << endl;
			ofLoadURLAsync(url, "random_image");
		}
		if(response.request.name == "random_image"){
			rimg.img->load(response.data);
			rimg.loading=false;
		}
	}else{
		cout << response.status << " " << response.error << " for request " << response.request.name << endl;
		if(response.status!=-1) rimg.loading=false;
	}
}

void ofxRandomImage::loadRandomImage(ofImage& image){
	rimg.img = &image;
	rimg.loading = true;

	std::string url = "";
	std::string id = "";

	switch(method){
		case 0: {
			string term = "openframeworks";
			int page = 1;
			url = "http://www.google.com/search?q="+term+"&tbm=isch&sout=1&tbs=isz&&start="+ofToString(page);
			id = "random_google_search";
			break;
		}
		case 1: {
			url = RandomPersonalPictureFinder::generateFileName();
			cout << url << endl;
			id = "random_google_search";
			break;
		}
	}

	ofLoadURLAsync(url, id);
}

std::string ofxRandomImage::getCurrentmageUrl(){
	return rimg.url;
}

std::string ofxRandomImage::parseFromGoogle(string content, int index){

	vector<std::string> urls;

	std::regex regEx("<table class=\"images_table\" style=\"table-layout:fixed\" [^>]+>(.*?)</table>");
	std::smatch match;
	std::regex_search(content, match, regEx);
	int found = match.size();

	if(found != 0) {

		string contents = match[0];

		std::regex imgRegEx("<img[^>]*src=\"([^\"]*)");
		std::smatch imgMatch;
		std::regex_search(contents, imgMatch, imgRegEx);

		for (size_t i = 0; i < imgMatch.size(); ++i){

			string contents = imgMatch[i];

			std::regex srcRegEx("src=\"(.*?).$");
			std::smatch srcMatch;
			std::regex_search(contents, srcMatch, srcRegEx);

			if (srcMatch.size()!=0) {

				string url = srcMatch[0];
				url = url.substr(5);
				cout << "url found: " << url << endl;
				urls.push_back(url);

			}

		}

	}

	if(urls.size()>0){
		return urls.at(0);
	}
	return "";
}

