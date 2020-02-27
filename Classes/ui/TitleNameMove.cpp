#include "TitleNameMove.h"

USING_NS_CC;

TitleNameMove * TitleNameMove::titleNameCreate()
{
	return TitleNameMove::create();
}

TitleNameMove::TitleNameMove()
{
}

TitleNameMove::~TitleNameMove()
{
}

void TitleNameMove::Init(cocos2d::Vec2 position, cocos2d::Vec2 scale, cocos2d::Layer * layer)
{
	setTexture("image/Environment/title.png");
	setName("titleName");
	setScale(scale.x, scale.y);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	setPosition(Vec2(position.x + visibleSize.width, visibleSize.height - this->getContentSize().height));
	layer->addChild(this, 1);

	time = 0;
	speed = 50;
	moveFlag = true;
	this->position = position;

	this->scheduleUpdate();
}

void TitleNameMove::update(float delta)
{
	time += delta;
	if (time >= 1 / 20 && getPosition().x >= position.x && moveFlag)
	{
		setPosition(getPosition().x - speed, getPosition().y);
		if (speed > 0)
		{
			speed -= delta;
		}
	}
	else
	{
		moveFlag = false;
	}

	if(!moveFlag)
	{
		setPosition(position.x, getPosition().y);
	}
}
