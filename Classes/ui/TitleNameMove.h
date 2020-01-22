#pragma once
#include "cocos2d.h"

class TitleNameMove : public cocos2d::Sprite
{
public:
	static TitleNameMove* titleNameCreate();
	TitleNameMove();
	~TitleNameMove();
	void Init(cocos2d::Vec2 position, cocos2d::Vec2 scale, cocos2d::Layer* layer);
	void update(float delta);
	CREATE_FUNC(TitleNameMove);
private:
	float time;
	cocos2d::Vec2 position;
	float speed;
};

