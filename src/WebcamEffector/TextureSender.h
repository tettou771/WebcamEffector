#pragma once

#include "ofxComponent.h"
#include "Cameras/WebcamEffectorBase.h"
#ifdef WIN32
	#include "ofxSpout.h"
#endif

using namespace ofxComponent;

class TextureSender : public ofxComponentBase {
public:
	void onSetup() override;
	void postUpdate() override;

private:

#ifdef WIN32
	ofxSpout::Sender sender;
#endif

};

