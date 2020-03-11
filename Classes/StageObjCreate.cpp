#include "StageObjCreate.h"
#include "obj/Player.h"
#define OBJ_LIMIT 20.0f

USING_NS_CC;

StageObjCreate * StageObjCreate::createStageObj()
{
	return StageObjCreate::create();
}

StageObjCreate::StageObjCreate()
{
}

StageObjCreate::~StageObjCreate()
{
}

void StageObjCreate::Init(std::string spName, Vec2 position, Vec2 scale, Layer* layer)
{
	setTexture("image/Sprites/stage/" + spName + ".png");
	setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	setPosition(position);
	setScale(scale.x, scale.y);
	layer->addChild(this, 3);
	velocity = Vec2(8.0f, 5.0f);
	blowOffFlag = false;
	time = 0;
	scheduleUpdate();
}

void StageObjCreate::update(float delta)
{
	// プレイヤーとオブジェクトの当たり判定
	auto player = (Player*)Director::getInstance()->getRunningScene()->getChildByName("plLayer")->getChildByName("Player");
	auto plRect = player->getBoundingBox();
	auto objRect = this->getBoundingBox();
	if (plRect.intersectsRect(objRect) && player->GetBigModeFlag())
	{
		blowOffFlag = true;
	}

	if (blowOffFlag)
	{
		// プレイヤーに当たったらオブジェクトは吹っ飛んでいく
		setPosition(Vec2(getPosition().x + velocity.x, getPosition().y + velocity.y));

		// 一定時間たったら消滅させる
		time += delta;
		if (time > OBJ_LIMIT)
		{
			this->removeFromParentAndCleanup(true);
		}
	}
	else if (getPosition().x < player->getPosition().x)
	{
		// 一定時間たったら消滅させる
		time += delta;
		if (time > OBJ_LIMIT)
		{
			this->removeFromParentAndCleanup(true);
		}
	}
}
