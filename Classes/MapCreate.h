#pragma once
#include "cocos2d.h"

class MapCreate : public cocos2d::Node
{
public:
	static cocos2d::Node* createMap();
	MapCreate();
	~MapCreate();
	void Init(cocos2d::Layer* layer);
	void update(float flam);
	cocos2d::TMXTiledMap* GetMap();
	CREATE_FUNC(MapCreate);
private:
	cocos2d::TMXTiledMap* mapA;
	cocos2d::TMXTiledMap* mapB;
};

