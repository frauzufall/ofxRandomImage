#pragma once

#include "ofMain.h"

class ofxRandomImageAPI
{
	public:
		ofxRandomImageAPI(){
			active.set(false);
		}
		virtual ~ofxRandomImageAPI(){}

		virtual bool loadFromXml(const ofXml& xml) = 0;

		virtual void setRandomImageUrl(std::string& url) = 0;

		virtual std::string getName() = 0;

		ofParameter<bool>& getActive(){
			return active;
		}

	protected:
		ofParameter<bool> active;
		std::string* url;
};
