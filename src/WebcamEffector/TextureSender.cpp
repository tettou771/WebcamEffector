#include "TextureSender.h"

void TextureSender::onSetup() {
#ifdef WIN32
	sender.init("WebcamEffector");
#endif
    
#ifdef TARGET_OS_MAC
    individualTextureSyphonServer.setName("Texture Output");
#endif
}

void TextureSender::postUpdate() {
#ifdef WIN32
	sender.send(WebcamEffectorBase::vcamFbo.getTexture());
#endif

#ifdef TARGET_OS_MAC
    individualTextureSyphonServer.publishTexture(&WebcamEffectorBase::vcamFbo.getTexture());
#endif
}
