#pragma once
#include "cocos2d.h"
#include <array>

class Score : public cocos2d::Sprite
{
public:
	static Score* createScore();			//クラスを生成
	Score();
	~Score();
	void Init(cocos2d::Layer* layer);
	void AddScore(int point);
	int GetScore();
	void DrawScore();
	void ResetScore();
	void update(float delta);				//毎フレーム更新関数
	CREATE_FUNC(Score);

private:
	float time;
	float waitTime;
	std::array<cocos2d::Sprite*, 6> numberSpList;
	std::array<std::string, 10> numList;
	std::array<cocos2d::Vec2, 6> rankPos;
	int number;
	int anser;
};

static int score;