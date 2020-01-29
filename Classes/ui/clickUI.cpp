#include "clickUI.h"
#define FLASHING_TIME 60

USING_NS_CC;

clickUI * clickUI::createClick()
{
	return clickUI::create();
}

clickUI::clickUI()
{
	time = 0;
}

clickUI::~clickUI()
{
}

void clickUI::Init(cocos2d::Vec2 position, cocos2d::Vec2 scale, cocos2d::Layer* layer)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	setTexture("image/Environment/pushA.png");
	setName("click");
	setScale(scale.x, scale.y);
	maxScale = scale;
	setPosition(position);
	layer->addChild(this, 1);
#else
	setTexture("image/Environment/click.png");
	setName("click");
	setScale(scale.x, scale.y);
	maxScale = scale;
	setPosition(position);
	layer->addChild(this, 1);
#endif
	
	this->scheduleUpdate();
}

void clickUI::update(float delta)
{
	//点滅動作
	time += delta;
	if ((time >= 0) && (time < 1.0f))
	{
		setScale(maxScale.x, maxScale.y);
	}
	else if ((time >= 1.0f) && (time < 1.0f * 2))
	{
		setScale(0, 0);
	}
	else
	{
		time = 0;
	}
}
