#include "BackScroll.h"

USING_NS_CC;

BackScroll * BackScroll::BackSrlCreate()
{
	return BackScroll::create();
}

BackScroll::BackScroll()
{
}

BackScroll::~BackScroll()
{
}

void BackScroll::Init(Vec2 position, Vec2 scale, Layer * layer)
{
	layer->addChild(this, 0);

	//背景A
	backA = Sprite::create();
	backA->setTexture("image/Environment/back_sky.png");
	backA->setName("backA");
	backA->setScale(scale.x, scale.y);
	backA->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	backA->setPosition(0, 0);
	layer->addChild(backA, 0);

	//背景B
	backB = Sprite::create();
	backB->setTexture("image/Environment/back_sky.png");
	backB->setName("backB");
	backB->setScale(scale.x, scale.y);
	backB->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	backB->setPosition(backA->getContentSize().width, 0);
	layer->addChild(backB, 0);
	this->scheduleUpdate();
}

void BackScroll::update(float delta)
{
	backA->setPositionX(backA->getPositionX() - 0.5f);
	backB->setPositionX(backB->getPositionX() - 0.5f);

	if (backB->getPositionX() < 0) {
		// 背景Aが画面左外に出きった場合、背景Aを背景Bの右隣に移す
		backA->setPositionX(backB->getPositionX() + backB->getContentSize().width);

		// 背景AとBの変数を入れ替える
		auto s = backB;
		backB = backA;
		backA = s;
	}
}
