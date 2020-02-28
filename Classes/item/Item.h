#pragma once
#include "cocos2d.h"

class Item : public cocos2d::Sprite
{
public:
	~Item() {};
	virtual void SetDeathFlag(bool flag) = 0;
	virtual bool GetDeathFlag() = 0;
protected:
	bool deathFlag;				// 死亡フラグ
	cocos2d::Action* action;	// アクション情報保存変数
};

