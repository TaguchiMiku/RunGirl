#pragma once
#include "cocos2d.h"

class Item : public cocos2d::Sprite
{
public:
	~Item() {};
	virtual void SetDeathFlag(bool flag) = 0;
	virtual bool GetDeathFlag() = 0;
protected:
	bool deathFlag;				// ���S�t���O
	cocos2d::Action* action;	// �A�N�V�������ۑ��ϐ�
};

