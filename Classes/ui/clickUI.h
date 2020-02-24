#pragma once
#include "cocos2d.h"

class ClickUI : public cocos2d::Sprite
{
public:
	static ClickUI* createClick();
	ClickUI();
	~ClickUI();
	void Init(cocos2d::Vec2 position, cocos2d::Vec2 scale, cocos2d::Layer* layer);
	void update(float delta);
	CREATE_FUNC(ClickUI);
private:
	float time;
	cocos2d::Vec2 maxScale;
};

