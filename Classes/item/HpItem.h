#pragma once
#include "cocos2d.h"

class HpItem : public cocos2d::Sprite
{
public:
	static HpItem* createHpItem();			//�N���X�𐶐�
	HpItem();
	~HpItem();
	void SetDeathFlag(bool flag);
	bool GetDeathFlag();
	CREATE_FUNC(HpItem);
private:
	bool deathFlag;
};

