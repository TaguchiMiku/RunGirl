#include "BackScroll.h"
#include "obj/Player.h"
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
	layer->addChild(this, 0);
	sclSpeed = speed;
	//背景A
	backA = Sprite::create();
	backA->setTexture("image/Environment/Layers/" + fileName + ".png");
	backA->setName("backA");
	backA->setScale(scale.x, scale.y);
	backA->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	backA->setPosition(0, 0);
	layer->addChild(backA, 0);

	//背景B
	backB = Sprite::create();
	backB->setTexture("image/Environment/Layers/" + fileName + ".png");
	backB->setName("backB");
	backB->setScale(scale.x, scale.y);
	backB->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	backB->setPosition(backA->getContentSize().width, 0);
	layer->addChild(backB, 0);

	this->scheduleUpdate();
}

void BackScroll::update(float delta)
{
	backA->setPositionX(backA->getPositionX() - sclSpeed * (1 - delta));
	backB->setPositionX(backB->getPositionX() - sclSpeed * (1 - delta));

	if (scrSetFlag) {
		// 背景Aが画面左外に出きった場合、背景Aを背景Bの右隣に移す
		backA->setPositionX(backB->getPositionX() + backB->getContentSize().width);

		// 背景AとBの変数を入れ替える
		auto s = backB;
		backB = backA;
		backA = s;
		scrSetFlag = false;
	}
}

void BackScroll::ScrBackSet(Vec2 position)
{
	if (backB->getPositionX() < position.x - visibleSize.x / 2)
	{
		scrSetFlag = true;
	}
}
