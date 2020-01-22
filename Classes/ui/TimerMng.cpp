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
	timer = 120;
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
	//画像読み込み（数字画像リスト）
	for (int num = 0; num < 10; num++)
	{
		numList[num] = "image/Sprites/numberA/_number_0" + std::to_string(num) + ".png";
	}
	//表示する座標リスト
	for (int j = 0; j < 3; j++)
	{
		timePos[j] = Vec2((Director::getInstance()->getVisibleSize().width / 2 - STRING_SIZE) + STRING_SIZE * j, Director::getInstance()->getVisibleSize().height - STRING_SIZE);
	}
	//描画するスプライト情報リスト(1の位から順に)
	for (int rank = 0; rank < 3; rank++)
	{
		numberSpList[rank] = Sprite::create("image/Sprites/numberA/_number_00.png");
		numberSpList[rank]->setScale(0.3f, 0.3f);
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
		if (anser <= 9 && cnt > 1)
		{
			numSp->setTexture(numList[anser]);
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
	time++;
	if ((time * (1 - delta)) >= 60)
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
