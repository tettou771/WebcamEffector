#pragma once
#include "ofxComponentBase.h"
using namespace ofxComponent;

class WebcamEffectorBase : public ofxComponentBase {
public:
	WebcamEffectorBase();
	~WebcamEffectorBase();

	void vcamDraw();
	virtual void onVcamDraw() { ; }

	static ofVideoGrabber webcam;
	static ofFbo vcamFbo;
	static const int vcamWidth = 1920;
	static const int vcamHeight = 1080;

	static void initializeOnWebcamEffectorManager();
	static void setCameraID(int id);
};

