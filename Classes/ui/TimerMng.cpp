#include "TimerMng.h"
#define STRING_SIZE 35
#define TEN 10

USING_NS_CC;

TimerMng * TimerMng::createTimer()
{
	return TimerMng::create();
}

TimerMng::TimerMng()
{
	time = 0;
	timer = 90;
	anser = 0;
	number = 0;
	cntTime = 0;
	this->scheduleUpdate();
}

TimerMng::~TimerMng()
{
}

void TimerMng::Init(cocos2d::Layer * layer)
{
	auto timerBack = Sprite::create("image/Environment/timerBack.png");
	timerBack->setScale(0.2f, 0.12f);
	timerBack->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	timerBack->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2 - STRING_SIZE * 2 - 8, Director::getInstance()->getVisibleSize().height + 3));
	layer->addChild(timerBack, 1);
	auto time = Sprite::create("image/Environment/time.png");
	time->setScale(0.5f, 0.5f);
	time->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	time->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2 - STRING_SIZE - 10, Director::getInstance()->getVisibleSize().height + 10));
	layer->addChild(time, 1);

	//画像読み込み（数字画像リスト）
	for (int num = 0; num < 10; num++)
	{
		numList[num] = "image/Sprites/numberA/_number_0" + std::to_string(num) + ".png";
	}
	//表示する座標リスト
	for (int j = 0; j < 3; j++)
	{
		timePos[j] = Vec2((Director::getInstance()->getVisibleSize().width / 2 - STRING_SIZE) + STRING_SIZE * j, Director::getInstance()->getVisibleSize().height - STRING_SIZE - 10);
	}
	//描画するスプライト情報リスト(1の位から順に)
	for (int rank = 0; rank < 3; rank++)
	{
		numberSpList[rank] = Sprite::create("image/Sprites/numberA/_number_00.png");
		numberSpList[rank]->setScale(0.2f, 0.2f);
		numberSpList[rank]->setPosition(timePos[2 - rank]);
		layer->addChild(numberSpList[rank], 1);
	}
	layer->addChild(this, 1);
}

void TimerMng::DrawTimer()
{
	int cnt = 1;
	anser = timer;
	for (auto numSp : numberSpList)
	{
		if (anser < 0)
		{
			break;
		}
		number = anser % TEN;
		anser = anser / TEN;
		numSp->setTexture(numList[number]);
		cnt += 10;
	}
}

int TimerMng::GetTimerCnt()
{
	return timer;
}

void TimerMng::update(float delta)
{
	if (Director::getInstance()->getRunningScene()->getName() != "Game")
	{
		return;
	}
	time += delta;
	if (time >= 1)
	{
		cntTime++;
		if (cntTime < 4)
		{
			time = 0;
			return;
		}
		time = 0;
		timer--;
	}
}
