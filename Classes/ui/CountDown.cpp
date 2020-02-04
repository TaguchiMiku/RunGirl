#include "CountDown.h"
#include "sound/SoundMng.h"
USING_NS_CC;

CountDown * CountDown::createCntDwn()
{
	return CountDown::create();
}

CountDown::CountDown()
{
	time = 0;
	cnt = 2;
	this->scheduleUpdate();
}

CountDown::~CountDown()
{
	if (sound)
	{
		sound->destroy();
	}
}

void CountDown::Init(cocos2d::Layer * layer)
{
	for (int num = 1; num < 4; num++)
	{
		numberSpList[num - 1] = Sprite::create("image/Sprites/numberB/_number_0" + std::to_string(num) + ".png");
		numberSpList[num - 1]->setScale(1.5f, 1.5f);
		numberSpList[num - 1]->setPosition(Director::getInstance()->getVisibleSize() / 2);
		layer->addChild(numberSpList[num - 1], 1);
	}
	layer->addChild(this, 1);
}

void CountDown::DrawCount()
{
}

void CountDown::update(float delta)
{
	if (Director::getInstance()->getRunningScene()->getName() != "Game")
	{
		return;
	}
	time += delta;
	if (time >= 1.0f)
	{
		time = 0;
		if (cnt >= 0)
		{
			numberSpList[cnt]->setScale(0, 0);
			cnt--;
		}
		if (cnt == 1)
		{
			sound = lpSoundMng.OnceSoundPlay("sound/GameScene.ckb");
		}
	}
}
