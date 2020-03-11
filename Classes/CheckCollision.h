#pragma once
#include "cocos2d.h"

struct actModule;
class Player;
struct CheckCollision
{
	//タイルチップとの当たり判定
	bool operator()(actModule& module);
private:
	cocos2d::Director* director;
	cocos2d::TMXTiledMap* map;
	cocos2d::TMXLayer* lay;
	cocos2d::Vec2 pos;
	cocos2d::Size visibleSize;
	Player* player;
	cocos2d::ValueMap properties;
};

