#include "Score.h"
#define TEN 10
#define STRING_SIZE 35

USING_NS_CC;

Score * Score::createScore()
{
	return Score::create();
}

Score::Score()
{
	time = 0;
	waitTime = 0;
	number = 0;
	anser = 0;
	this->scheduleUpdate();
}

Score::~Score()
{
}

void Score::Init(cocos2d::Layer * layer, float strSize, Vec2 scale)
{
	//画像読み込み（数字画像リスト）
	for (int num = 0; num < 10; num++)
	{
		numList[num] = "image/Sprites/numberC/_number_0" + std::to_string(num) + ".png";
	}
	//表示する座標リスト
	for (int j = 0; j < 6; j++)
	{
		rankPos[j] = Vec2(this->getPosition().x + strSize * j, this->getPosition().y + Director::getInstance()->getVisibleSize().height - STRING_SIZE * 2);
	}
	//描画するスプライト情報リスト(1の位から順に)
	for (int rank = 0; rank < 6; rank++)
	{
		numberSpList[rank] = Sprite::create("image/Sprites/numberC/_number_00.png");
		numberSpList[rank]->setScale(scale.x, scale.y);
		numberSpList[rank]->setPosition(rankPos[5 - rank]);
		layer->addChild(numberSpList[rank], 1);
	}
}

void Score::AddScore(int point)
{
	score += point;
}

void Score::AddCandy(int point)
{
	candy += point;
}

void Score::AddLight(int point)
{
	light += point;
}

int Score::GetCandy()
{
	return candy;
}

int Score::GetLight()
{
	return light;
}

int Score::GetScore()
{
	return score;
}

void Score::DrawScore()
{
	int cnt = 1;
	anser = score;
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

void Score::ResetScore()
{
	score = 0;
	candy = 0;
	light = 0;
}

void Score::update(float delta)
{
	if (Director::getInstance()->getRunningScene()->getName() != "Game")
	{
		return;
	}
	waitTime += delta;
	if (waitTime <= 3)
	{
		return;
	}
	time += delta;
	if (time >= 1)
	{
		time = 0;
		score++;
	}
}
