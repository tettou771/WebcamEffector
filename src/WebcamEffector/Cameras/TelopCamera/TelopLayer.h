#pragma once
#include <codecvt>
#include "ofxComponent.h"

#define TELOP_USE_OSC

#ifdef TELOP_USE_MQTT
#include "ofxMQTT.h"
#endif
#ifdef TELOP_USE_OSC
#include "ofxOsc.h"
#endif

using namespace ofxComponent;

class TelopLayer :public ofxComponentBase{
public:
    TelopLayer();
    ~TelopLayer();
    
	void onSetup() override;
	void onUpdate() override;
	void onDraw() override;
    
	void setTelopText(string telopText);
	void clearTelopText();
	void drawTelop();

private:
	ofFbo fbo;
	string trimmedTelopText, receivedTelopText;
	ofTrueTypeFont telopFont;

#ifdef WIN32
	// 表示文字数の調整のために必要な変換器(UTF8 UTF32)
	// char32_t を使うとVS2015でリンクエラーとなるので、unit32_t を使っている
	// ソース Qiita http://qiita.com/benikabocha/items/1fc76b8cea404e9591cf
	wstring_convert<codecvt_utf8<uint32_t>, uint32_t> convert8_32;
#else
    // macの場合は上記の工夫は必要ないので、char32_t を使う
    wstring_convert<codecvt_utf8<char32_t>, char32_t> convert8_32;
#endif
	string UTF32toUTF8(u32string& u32str);
	u32string UTF8toUTF32(string& str);

#ifdef TELOP_USE_MQTT
	ofxMQTT client;

	// MQTT handlers
	void onOnline();
	void onOffline();
	void onMessage(ofxMQTTMessage& msg);
	void publish(string _topic, string _message);
#endif

#ifdef TELOP_USE_OSC
	ofxOscReceiver oscReceiver;
#endif

	// clear if timeout
	float pastSetTelopTime; // sec
	float telopShowDuration; // sec
    string telopShowed;
};

