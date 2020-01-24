#pragma once
#include "cocos2d.h"

class clickUI : public cocos2d::Sprite
{
public:
	static clickUI* createClick();
	clickUI();
	~clickUI();
	void Init(cocos2d::Vec2 position, cocos2d::Vec2 scale, cocos2d::Layer* layer);
	void update(float delta);
	CREATE_FUNC(clickUI);
private:
	float time;
	cocos2d::Vec2 maxScale;
};

