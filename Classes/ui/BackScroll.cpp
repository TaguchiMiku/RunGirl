#include "BackScroll.h"
#include "obj/Player.h"
#include "debug/_DebugConOut.h"
USING_NS_CC;

BackScroll * BackScroll::BackSrlCreate()
{
	return BackScroll::create();
}

BackScroll::BackScroll()
{
	scrSetFlag = false;
	visibleSize = Director::getInstance()->getVisibleSize();
}

BackScroll::~BackScroll()
{
}

void BackScroll::Init(std::string fileName, Vec2 position, Vec2 scale, Layer * layer, float speed)
{
	sclSpeed = speed;
	//背景A
	backA = Sprite::create("image/Environment/Layers/Clouds_4_2.png"/* + fileName + ".png"*/);
	backA->setScale(scale.x, scale.y);
	backA->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	backA->setPosition(0, 0);
	layer->addChild(backA, 0);
	//背景B
	backB = Sprite::create("image/Environment/Layers/Clouds_4_2.png"/* + fileName + ".png"*/);
	backB->setScale(scale.x, scale.y);
	backB->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	backB->setPosition(backA->getContentSize().width / 2.0f, 0);
	layer->addChild(backB, 0);

	layer->addChild(this, 0);
	this->scheduleUpdate();
}

void BackScroll::update(float delta)
{
	backA->setPositionX(backA->getPositionX() - sclSpeed);
	backB->setPositionX(backB->getPositionX() - sclSpeed);
}

void BackScroll::ScrBackSet(Vec2 position)
{
	if (position.x > (backA->getPositionX() + backA->getContentSize().width))
	{
		backA->setPositionX(backB->getPositionX() + backB->getContentSize().width / 2.0f);
	}
	if (position.x > (backB->getPositionX() + backB->getContentSize().width))
	{
		backB->setPositionX(backA->getPositionX() + backA->getContentSize().width / 2.0f);
	}
}
