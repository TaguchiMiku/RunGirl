#pragma once
#include "cocos2d.h"

class NormalItem : public cocos2d::Sprite
{
public:
	static NormalItem* createNItem();			//クラスを生成
	NormalItem();
	~NormalItem();
	void SetDeathFlag(bool flag);
	bool GetDeathFlag();
	CREATE_FUNC(NormalItem);
private:
	bool deathFlag;
};

