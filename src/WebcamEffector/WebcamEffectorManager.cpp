#include "WebcamEffectorManager.h"

WebcamEffectorManager::WebcamEffectorManager() {
}

WebcamEffectorManager::~WebcamEffectorManager() {
}

void WebcamEffectorManager::onSetup() {
	//setWidth(WebcamEffectorBase::vcamWidth);
	//setHeight(WebcamEffectorBase::vcamHeight);
	setRect(ofRectangle(0, 0, ofGetWidth(), ofGetWidth() * WebcamEffectorBase::vcamHeight / WebcamEffectorBase::vcamWidth));

	cameras.push_back(telopCamera = make_shared<TelopCamera>());

	for (auto& c : cameras) {
		addChild(c);
		c->setActive(false);
	}

	selectedCamera = cameras.front();
	selectedCamera->setActive(true);

	WebcamEffectorBase::initializeOnWebcamEffectorManager();

	// Initialise the Spout sender with a channel name
	sender.init("Camera");

}

void WebcamEffectorManager::onUpdate() {
	WebcamEffectorBase::webcam.update();
}

void WebcamEffectorManager::postUpdate() {
	if (selectedCamera) {
		selectedCamera->vcamDraw();
	}
	sender.send(WebcamEffectorBase::vcamFbo.getTexture());
}

void WebcamEffectorManager::onDraw() {
	WebcamEffectorBase::vcamFbo.draw(0, 0, getWidth(), getHeight());
}

void WebcamEffectorManager::onKeyPressed(ofKeyEventArgs& key) {
	if ('0' <= key.key && key.key <= '9') {
		int n = key.key - '0';
		WebcamEffectorBase::setCameraID(n);
	}
}
