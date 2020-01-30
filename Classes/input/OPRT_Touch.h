#pragma once
#include "OPRT_State.h"
struct OPRT_Touch : OPRT_State
{
	OPRT_Touch();
	OPRT_Touch(Node * nd);
	~OPRT_Touch();

	TYPE GetType() {
		return TYPE::TOUCH;
	}
	void Update()override;

private:
	cocos2d::Vec2 touchPos;
	cocos2d::Size windowSize;
	cocos2d::EventListenerTouchOneByOne* listener;
	cocos2d::EventKeyboard::KeyCode key;
	bool pushFlag;
};

