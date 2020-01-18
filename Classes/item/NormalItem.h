#pragma once
#include "cocos2d.h"

class NormalItem : public cocos2d::Sprite
{
public:
	static cocos2d::Sprite* createNItem(const char* fileName);			//ƒNƒ‰ƒX‚ğ¶¬
	NormalItem();
	~NormalItem();
	void Init();
};

