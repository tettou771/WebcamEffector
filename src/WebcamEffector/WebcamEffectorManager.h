#pragma once
#include "ofxSpout.h"
#include "ofxComponent.h"
#include "Cameras/TelopCamera/TelopCamera.h"

using namespace ofxComponent;

class WebcamEffectorManager : public ofxComponentBase {
public:
	WebcamEffectorManager();
	~WebcamEffectorManager();

	void onSetup() override;
	void onUpdate() override;
	void postUpdate() override;
	void onDraw() override;

	void onKeyPressed(ofKeyEventArgs& key) override;

private:
	vector<shared_ptr<WebcamEffectorBase> > cameras;
	shared_ptr<WebcamEffectorBase> selectedCamera;

	shared_ptr<TelopCamera> telopCamera;

	ofxSpout::Sender sender;
};

