#pragma once
#include "cocos2d.h"
#include <array>

class CkSound;
class CountDown : public cocos2d::Sprite
{
public:
	static CountDown* createCntDwn();			//�N���X�𐶐�
	CountDown();
	~CountDown();
	void Init(cocos2d::Layer* layer);
	void DrawCount();
	void update(float delta);				//���t���[���X�V�֐�
	CREATE_FUNC(CountDown);
private:
	float time;
	int cnt;
	std::array<cocos2d::Sprite*, 3> numberSpList;
	CkSound* sound;
};

