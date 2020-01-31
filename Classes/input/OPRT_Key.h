#pragma once
#include "OPRT_State.h"
struct OPRT_Key : OPRT_State
{
	OPRT_Key();
	OPRT_Key(Node * nd);
	~OPRT_Key();

	TYPE GetType()override {
		return TYPE::KEY;
	}
	void Update()override;

private:
	cocos2d::EventListenerKeyboard* listener;
	cocos2d::EventListenerTouchOneByOne* listener_mouse;
	cocos2d::EventKeyboard::KeyCode key;
	bool pushFlag;
	bool clickFlag;
};

