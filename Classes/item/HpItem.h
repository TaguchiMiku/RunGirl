#pragma once
#include "cocos2d.h"

class HpItem : public cocos2d::Sprite
{
public:
	static cocos2d::Sprite* createHpItem(const char* fileName);			//�N���X�𐶐�
	HpItem();
	~HpItem();
	void Init();
};

