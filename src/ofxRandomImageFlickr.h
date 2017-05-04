#pragma once

#include "ofxRandomImageAPI.h"

class ofxRandomImageFlickr : public ofxRandomImageAPI
{
	public:
		ofxRandomImageFlickr();
		~ofxRandomImageFlickr();

		void setup(std::string key);

		virtual bool loadFromXml(const ofXml& xml);

		virtual void setRandomImageUrl(std::string& url);

		virtual std::string getName();

		void urlResponse(ofHttpResponse & response);

	private:
		std::string key;
		int maxId;
		bool urlWaiting;

};
