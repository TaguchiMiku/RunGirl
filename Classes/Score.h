#pragma once
#include "cocos2d.h"
class Score : public cocos2d::Sprite
{
public:
	static Score* createScore();			//クラスを生成
	Score();
	~Score();
	void AddScore(int point);
	int GetScore();
	cocos2d::Label* DrawScore();
	void update(float delta);				//毎フレーム更新関数
	CREATE_FUNC(Score);

private:
	int score;
	float time;
};