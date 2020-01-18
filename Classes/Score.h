#pragma once
#include "cocos2d.h"
class Score : public cocos2d::Sprite
{
public:
	static Score* createScore();			//�N���X�𐶐�
	Score();
	~Score();
	void AddScore(int point);
	int GetScore();
	cocos2d::Label* DrawScore();
	void update(float delta);				//���t���[���X�V�֐�
	CREATE_FUNC(Score);

private:
	int score;
	float time;
};