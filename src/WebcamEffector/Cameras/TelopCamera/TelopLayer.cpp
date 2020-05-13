#include "TelopLayer.h"
#include <locale.h>

TelopLayer::TelopLayer() {
}
TelopLayer::~TelopLayer() {
}

void TelopLayer::onSetup() {
    setlocale( LC_CTYPE, "ja_JP.UTF-8");
	fbo.allocate(getWidth(), getHeight(), GL_RGBA);

	// font for telop
	string path = "fonts/GenEiGothicP-Bold.otf";
#ifdef _DEBUG
	float fontSize = 40; // smaller to fast debug
#else
	float fontSize = 80;
#endif
	ofTrueTypeFontSettings settings(path, fontSize);
	settings.addRanges(ofAlphabet::Latin);
	settings.addRanges(ofAlphabet::Japanese);
	settings.antialiased = false;
	telopFont.load(settings);
	setTelopText("telop sample");

#ifdef TELOP_USE_MQTT
	client.begin("localhost", 8883);
	client.connect("VirtualWebcam_" + ofToString(ofRandom(1000000)), "", "");
	ofAddListener(client.onOnline, this, &TelopLayer::onOnline);
	ofAddListener(client.onOffline, this, &TelopLayer::onOffline);
	ofAddListener(client.onMessage, this, &TelopLayer::onMessage);
#endif

#ifdef TELOP_USE_OSC
	oscReceiver.setup(8884);
#endif

	telopShowDuration = 2.0;
}

void TelopLayer::onUpdate() {
#ifdef TELOP_USE_MQTT
	client.update();
#endif

#ifdef TELOP_USE_OSC
	if (oscReceiver.hasWaitingMessages()){
		auto msg = ofxOscMessage();
		oscReceiver.getNextMessage(msg);
		if (msg.getAddress() == "/telop/text") {
			if (msg.getTypeString() == "s") {
				string text = msg.getArgAsString(0);
				setTelopText(text);
			}
		}
	}
#endif

	// clear expired telop
	if (ofGetElapsedTimef() - pastSetTelopTime > telopShowDuration && trimmedTelopText != "") {
		clearTelopText();
	}
}

void TelopLayer::onDraw() {
}

void TelopLayer::setTelopText(string text) {
	if (fbo.getWidth() <= 0) return;
    
    receivedTelopText = text;
    
    if (telopShowed.length() < text.length()) {
        int l = telopShowed.length();
        if (telopShowed == text.substr(0, telopShowed.length())) {
            text = text.substr(l, text.length() - l);
        } else {
            int i = 0;
            for (; i < l; ++i) {
                if (text[i] != telopShowed[i]) {
                    break;
                }
                if (i > 0) {
                    telopShowed = text.substr(0, i - 1);
                }else{
                    telopShowed = "";
                }
            }
        }
    } else {
        telopShowed = "";
        ofLog() << "showed clear";
    }
    
	// trim telop text to shorten
	int lineLength = 10; // num of characters per line
	int maxLineNum = 2; // num of max lines
	auto u32Text = UTF8toUTF32(text);
	if (u32Text.length() < lineLength) {
		trimmedTelopText = text;
	}
	else {
		u32string u32ShortText;
		bool firstline = true;
		int begin = (u32Text.length() - lineLength * (maxLineNum - 1) - 1) / lineLength * lineLength;
		if (begin < 0) begin = 0;
		for (int i = begin; i < u32Text.length(); i += lineLength) {
			if (!firstline) {
				u32ShortText += U'\n';
			}
			u32ShortText += u32Text.substr(i, MIN(lineLength, u32Text.length() - i));
			firstline = false;
		}
		string shortText = UTF32toUTF8(u32ShortText);
		trimmedTelopText = shortText;
	}

	fbo.begin();
	ofClear(0, 0);

	// calc telop geometry to centering
	auto bbox = telopFont.getStringBoundingBox(trimmedTelopText, 0, 0);
	float bottomMargin = 10;
	ofVec2f offset(-bbox.width / 2, - (bbox.height + bbox.y) - bottomMargin);
	ofVec2f center(getWidth() / 2, getHeight());
	float fontMagnitude = 160.0 / telopFont.getSize();
	float maxWidth = getWidth() * 0.8;
	float scale = MIN(fontMagnitude, maxWidth / bbox.width);

	ofPushMatrix();
	ofTranslate(center);
	ofScale(scale);
	ofTranslate(offset);

	// draw white outline
	ofSetColor(255);
	for (int i = 0, N = 16; i < N; ++i) {
		float t = TWO_PI * i / N;
		float r = bottomMargin * 0.5;
		float x = r * sin(t);
		float y = r * cos(t);
		telopFont.drawString(trimmedTelopText, x, y);
	}

	// draw colored
	ofSetColor(20, 20, 150);
	telopFont.drawString(trimmedTelopText, 0, 0);

	ofPopMatrix();
	fbo.end();

	pastSetTelopTime = ofGetElapsedTimef();
    
    ofLog() << telopShowed;
}

void TelopLayer::clearTelopText() {
    telopShowed = receivedTelopText;
    fbo.begin();
    ofClear(0, 0);
    fbo.end();
}

void TelopLayer::drawTelop() {
	if (fbo.getWidth() <= 0) return;
	fbo.draw(0, 0);
}

string TelopLayer::UTF32toUTF8(u32string& u32str) {
	return convert8_32.to_bytes(reinterpret_cast<const char32_t*>(u32str.c_str()));
}

u32string TelopLayer::UTF8toUTF32(string& str) {
	auto A = convert8_32.from_bytes(str);
	return u32string(A.cbegin(), A.cend());
}

#ifdef TELOP_USE_MQTT
void TelopLayer::onOnline() {
	ofLog() << "MQTT online";

	client.subscribe("telop");
}

void TelopLayer::onOffline() {
}

void TelopLayer::onMessage(ofxMQTTMessage& msg) {
	setTelopText(msg.payload);
}

void TelopLayer::publish(string _topic, string _message) {
}
#endif
