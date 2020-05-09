#include "TextureSender.h"

void TextureSender::onSetup() {
#ifdef WIN32
	sender.init("WebcamEffector");
#endif
}

void TextureSender::postUpdate() {
#ifdef WIN32
	sender.send(WebcamEffectorBase::vcamFbo.getTexture());
#endif
}
