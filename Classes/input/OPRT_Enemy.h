#pragma once
#include "OPRT_State.h"
class OPRT_Enemy : public OPRT_State
{
public:
	OPRT_Enemy();
	~OPRT_Enemy();
	TYPE GetType() {
		return TYPE::KEY;
	}
	void Update();

private:
	cocos2d::EventKeyboard::KeyCode key;
};

