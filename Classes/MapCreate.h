#pragma once
#include "cocos2d.h"
#include <vector>

class EnemyCreate;
class ItemCreate;
class MapCreate : public cocos2d::Node
{
public:
	static cocos2d::Node* createMap();
	MapCreate();
	~MapCreate();
	void Init(cocos2d::Layer* layer);
	void update(float flam);
	cocos2d::TMXTiledMap* GetMap();
	cocos2d::Size GetMapSize();
	EnemyCreate* GetEnemyCt();
	ItemCreate* GetItemCt();;

	void ReCreate(cocos2d::TMXTiledMap* map, cocos2d::Layer* layer);
	CREATE_FUNC(MapCreate);
private:
	cocos2d::TMXTiledMap* nowMap;
	cocos2d::TMXTiledMap* nextMap;
	std::vector<cocos2d::TMXTiledMap*> map;
	cocos2d::Size mapSize;
	cocos2d::Director* director;
	EnemyCreate* enemyCt;
	ItemCreate* itemCt;
	bool setMapFlag;
	cocos2d::Layer* layer;
};

