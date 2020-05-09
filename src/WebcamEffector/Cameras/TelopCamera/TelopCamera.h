#pragma once
#include "TelopLayer.h"
#include "../WebcamEffectorBase.h"

class TelopCamera : public WebcamEffectorBase {
public:
	void onSetup();
	void onUpdate();
	void onVcamDraw();
	void onDraw();

private:
	shared_ptr<TelopLayer> telopLayer;
};

