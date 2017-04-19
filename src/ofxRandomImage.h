#pragma once
#include "ofMain.h"

struct ofxRandomImageObject {
	ofImage* img;
	std::string url;
	bool loading;
};

class ofxRandomImage {

	public:

		ofxRandomImage();
		~ofxRandomImage();

		void setup();

		void urlResponse(ofHttpResponse & response);

		void loadRandomImage(ofImage& image);
		std::string getCurrentmageUrl();

		static std::string parseFromGoogle(string content, int index = 0);

	private:

		ofxRandomImageObject rimg;
		int method = 1;

};

