#pragma once
#include <codecvt>
#include "ofxComponent.h"
#include "ofxMQTT.h"

using namespace ofxComponent;

class TelopLayer :public ofxComponentBase{
public:
	void onSetup();
	void onUpdate();
	void onDraw();

	void setTelopText(string telopText);
	void clearTelopText();
	void drawTelop();

private:
	ofFbo fbo;
	string telopText;
	ofTrueTypeFont telopFont;

	// �\���������̒����̂��߂ɕK�v�ȕϊ���(UTF8 UTF32)
	// char32_t ���g����VS2015�Ń����N�G���[�ƂȂ�̂ŁAunit32_t ���g���Ă���
	// �\�[�X Qiita http://qiita.com/benikabocha/items/1fc76b8cea404e9591cf
	wstring_convert<codecvt_utf8<uint32_t>, uint32_t> convert8_32;
	string UTF32toUTF8(u32string& u32str);
	u32string UTF8toUTF32(string& str);

	ofxMQTT client;

	// MQTT handlers
	void onOnline();
	void onOffline();
	void onMessage(ofxMQTTMessage& msg);
	void publish(string _topic, string _message);

	// clear if timeout
	float pastSetTelopTime; // sec
	float telopShowDuration; // sec
};
