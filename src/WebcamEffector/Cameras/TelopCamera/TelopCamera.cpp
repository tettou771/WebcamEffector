#include "TelopCamera.h"

void TelopCamera::onSetup() {
	setWidth(vcamWidth);
	setHeight(vcamHeight);

	addChild(telopLayer = make_shared<TelopLayer>());
	telopLayer->setRect(ofRectangle(0, 0, vcamWidth, vcamHeight));
}

void TelopCamera::onUpdate() {
}

void TelopCamera::onVcamDraw() {
	webcam.draw(0, 0, vcamWidth, vcamHeight);
	telopLayer->drawTelop();
}

void TelopCamera::onDraw() {
}
