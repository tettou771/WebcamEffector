#include "WebcamEffectorBase.h"

ofVideoGrabber WebcamEffectorBase::webcam;
ofFbo WebcamEffectorBase::vcamFbo;

WebcamEffectorBase::WebcamEffectorBase() {
}

WebcamEffectorBase::~WebcamEffectorBase() {
}

void WebcamEffectorBase::vcamDraw() {
	if (vcamFbo.getWidth() <= 0) return;

	vcamFbo.begin();
	onVcamDraw();
	vcamFbo.end();
}

void WebcamEffectorBase::initializeOnWebcamEffectorManager() {
	vcamFbo.allocate(WebcamEffectorBase::vcamWidth, WebcamEffectorBase::vcamHeight, GL_RGB);

	// webcam setup
	for (auto cam : webcam.listDevices()) {
		if (ofIsStringInString(cam.deviceName, "Snap")) {
			webcam.setDeviceID(cam.id);
			webcam.initGrabber(1280, 720);
		}
	}
}

void WebcamEffectorBase::setCameraID(int id) {
	webcam.close();

	webcam.setDeviceID(id);
	bool succeeded = webcam.initGrabber(1280, 720);
	if (webcam.getWidth() <= 0) {
		webcam.initGrabber(640, 480);
	}
}
