#pragma once
#include "ofMain.h"
#include "ofxRandomImageAPI.h"

struct ofxRandomImageObject {
	ofImage* img = 0;
	std::string url = "";
	bool waiting = false;
	bool loading = false;
};

class ofxRandomImage {

	public:

		ofxRandomImage();
		~ofxRandomImage();

		void setup();
		void update();

		void urlResponse(ofHttpResponse & response);

		void loadRandomImage(ofImage& image);
		std::string getCurrentmageUrl();

		static std::string parseFromGoogle(string content, int index = 0);

	private:

		vector<ofxRandomImageAPI*> apis;

		ofxRandomImageObject rimg;
		int method = 1;

};

