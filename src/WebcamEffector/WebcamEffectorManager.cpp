#include "WebcamEffectorManager.h"

WebcamEffectorManager::WebcamEffectorManager() {
}

WebcamEffectorManager::~WebcamEffectorManager() {
}

void WebcamEffectorManager::onSetup() {
	//setWidth(WebcamEffectorBase::vcamWidth);
	//setHeight(WebcamEffectorBase::vcamHeight);
	setRect(ofRectangle(0, 0, ofGetWidth(), ofGetWidth() * WebcamEffectorBase::vcamHeight / WebcamEffectorBase::vcamWidth));

	effectors.push_back(telopCamera = make_shared<TelopCamera>());
	for (auto& c : effectors) {
		addChild(c);
		c->setActive(false);
	}

	addChild(make_shared<TextureSender>());

	selectedEffect = effectors.front();
	selectedEffect->setActive(true);

	WebcamEffectorBase::initializeOnWebcamEffectorManager();

	// make list
	ofVideoGrabber v;
	cameraList = "Press num key to change source camera\n\n";
	for (auto c : v.listDevices()) {
		cameraList += ofToString(c.id) + ": " + c.deviceName + "\n";
	}
}

void WebcamEffectorManager::onUpdate() {
	WebcamEffectorBase::webcam.update();
}

void WebcamEffectorManager::postUpdate() {
	if (selectedEffect) {
		selectedEffect->vcamDraw();
	}
}

void WebcamEffectorManager::onDraw() {
	WebcamEffectorBase::vcamFbo.draw(0, 0, getWidth(), getHeight());
	ofDrawBitmapString(cameraList, 10, 20);
}

void WebcamEffectorManager::onKeyPressed(ofKeyEventArgs& key) {
	if ('0' <= key.key && key.key <= '9') {
		int n = key.key - '0';
		WebcamEffectorBase::setCameraID(n);
	}
}
