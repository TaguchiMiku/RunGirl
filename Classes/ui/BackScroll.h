#pragma once
#include "cocos2d.h"
class Player;
class BackScroll : public cocos2d::Sprite
{
public:
	static BackScroll* BackSrlCreate();
	BackScroll();
	~BackScroll();
	void Init(std::string fileName, cocos2d::Vec2 position, cocos2d::Vec2 scale, cocos2d::Layer* layer, float speed);
	void update(float delta);
	void ScrBackSet(cocos2d::Vec2 position);
	CREATE_FUNC(BackScroll);
private:
	cocos2d::Sprite* backA;
	cocos2d::Sprite* backB;
	cocos2d::Sprite* backC;
	bool scrSetFlag;
	cocos2d::Vec2 visibleSize;
	float sclSpeed;
};

