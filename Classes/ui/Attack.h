#pragma once
#include "cocos2d.h"
class Attack : public cocos2d::Sprite
{
public:
	static Attack* createAttack();
	Attack();
	~Attack();
	void Init(cocos2d::Vec2 position, cocos2d::Vec2 scale, cocos2d::Layer* layer);
	CREATE_FUNC(Attack);
};

