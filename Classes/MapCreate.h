#pragma once
#include "cocos2d.h"
#include <vector>
#include <map>

class EnemyCreate;
class ItemGenerate;
class StageObjCreate;
class MapCreate : public cocos2d::Node
{
public:
	MapCreate();
	~MapCreate();
	static cocos2d::Node* createMap();
	void Init(cocos2d::Layer* layer);
	void update(float flam);
	cocos2d::TMXTiledMap* GetMap();
	cocos2d::TMXTiledMap* GetNextMap();
	cocos2d::Size GetMapSize();
	EnemyCreate* GetEnemyCt();
	ItemGenerate* GetItemCt();
	bool GetMapSetFlag();

	void PutSprite(cocos2d::TMXTiledMap* map);
	void ReCreate(cocos2d::TMXTiledMap* map, cocos2d::Layer* layer);
	CREATE_FUNC(MapCreate);
private:
	cocos2d::TMXTiledMap* nowMap;		// ���ݕ\������Ă���}�b�v
	cocos2d::TMXTiledMap* nextMap;		// ���ɕ\������\��̃}�b�v
	std::map<std::string, cocos2d::TMXTiledMap*> map;
	std::vector<std::string> mapName;	// �}�b�v�̓o�^���O���X�g
	cocos2d::Size mapSize;
	cocos2d::Director* director;
	EnemyCreate* enemyNow;
	ItemGenerate* itemNow;
	EnemyCreate* enemyNext;
	ItemGenerate* itemNext;
	bool setMapFlag;
	bool setObjFlag;
	cocos2d::Layer* layer;
};

