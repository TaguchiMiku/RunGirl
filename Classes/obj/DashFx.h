#pragma once
#include "cocos2d.h"

class DashFx : public cocos2d::Sprite
{
public:
	static DashFx* createDash();			//クラスを生成
	DashFx();
	~DashFx();
	void SetDeathFlag(bool flag);
	bool GetDeathFlag();
	CREATE_FUNC(DashFx);
private:
	bool deathFlag;
};

