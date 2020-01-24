#pragma once
#include "cocos2d.h"
#include <array>

class TimerMng : cocos2d::Sprite
{
public:
	static TimerMng* createTimer();			//クラスを生成
	TimerMng();
	~TimerMng();
	void Init(cocos2d::Layer* layer);
	void DrawTimer();
	int GetTimerCnt();
	void update(float delta);				//毎フレーム更新関数
	CREATE_FUNC(TimerMng);

private:
	float time;
	int timer;
	std::array<cocos2d::Sprite*, 3> numberSpList;
	std::array<std::string, 10> numList;
	std::array<cocos2d::Vec2, 3> timePos;
	int anser;
	int number;
	int cntTime;
};

