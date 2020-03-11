#pragma once
#include "cocos2d.h"

class Glass : public cocos2d::Sprite
{
public:
	Glass();
	~Glass();
	Glass * Glass::createGlass();
	void Init();
	CREATE_FUNC(Glass);
private:
	cocos2d::Action* action;
};

