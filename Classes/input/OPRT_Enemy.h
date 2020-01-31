#pragma once
#include "OPRT_State.h"
#include "obj/Unit.h"
class Enemy;
class OPRT_Enemy : public OPRT_State
{
public:
	OPRT_Enemy();
	OPRT_Enemy(Unit* unit);
	~OPRT_Enemy();
	TYPE GetType()override {
		return TYPE::KEY;
	}
	void Update()override;

private:
	cocos2d::EventKeyboard::KeyCode key;
	Unit* unit;
	cocos2d::Rect plRect;
	cocos2d::Rect enRect;
	bool jumpFlag;
};

