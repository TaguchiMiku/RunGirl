﻿#pragma once
#include "cocos2d.h"
class BackScroll : public cocos2d::Sprite
{
public:
	static BackScroll* BackSrlCreate();
	BackScroll();
	~BackScroll();
	void Init(cocos2d::Vec2 position, cocos2d::Vec2 scale, cocos2d::Layer* layer);
	void update(float delta);
	CREATE_FUNC(BackScroll);
private:
	cocos2d::Sprite* backA;
	cocos2d::Sprite* backB;
};

