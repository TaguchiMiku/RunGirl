#include "TitleNameMove.h"

USING_NS_CC;

TitleNameMove * TitleNameMove::titleNameCreate()
{
	return TitleNameMove::create();
}

TitleNameMove::TitleNameMove()
{
	time = 0;
	speed = 50;
}

TitleNameMove::~TitleNameMove()
{
}

void TitleNameMove::Init(cocos2d::Vec2 position, cocos2d::Vec2 scale, cocos2d::Layer * layer)
{
	setTexture("image/Environment/title.png");
	setName("titleName");
	setScale(scale.x, scale.y);
	this->position = position;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	setPosition(Vec2(visibleSize.width + 500, position.y));
	layer->addChild(this, 1);
	this->scheduleUpdate();
}

void TitleNameMove::update(float delta)
{
	time += delta;
	if (time >= 1 / 20 && getPosition().x >= position.x)
	{
		setPosition(getPosition().x - speed, getPosition().y);
		if (speed > 0)
		{
			speed--;
		}
	}
}
