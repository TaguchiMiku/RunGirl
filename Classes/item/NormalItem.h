#pragma once
#include "cocos2d.h"

class NormalItem : public cocos2d::Sprite
{
public:
	static cocos2d::Sprite* createNItem(const char* fileName);			//�N���X�𐶐�
	NormalItem();
	~NormalItem();
	void Init();
};

