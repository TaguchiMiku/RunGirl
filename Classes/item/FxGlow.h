#pragma once
#include "cocos2d.h"

class FxGlow : public cocos2d::Sprite
{
public:
	static FxGlow* createHpItem();			//クラスを生成
	FxGlow();
	~FxGlow();
	void SetDeathFlag(bool flag);
	bool GetDeathFlag();
	CREATE_FUNC(FxGlow);
private:
	bool deathFlag;
	cocos2d::Action* action;
};

