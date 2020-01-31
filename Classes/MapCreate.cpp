#include "MapCreate.h"
#include "obj/Enemy.h"
#include "item/HpItem.h"
#include "item/NormalItem.h"
#include "EnemyCreate.h"
#include "ItemCreate.h"
#include "debug/_DebugConOut.h"
#define PL_SIZE_X 34
USING_NS_CC;

cocos2d::Node * MapCreate::createMap()
{
	return MapCreate::create();
}

MapCreate::MapCreate()
{
	mapSize = Vec2(0, 0);
	setMapFlag = false;
}

MapCreate::~MapCreate()
{
}

void MapCreate::Init(cocos2d::Layer * layer)
{
	director = Director::getInstance();
	auto mapA = TMXTiledMap::create("image/Environment/mapA.tmx");
	mapA->setName("map");
	mapA->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	mapA->setPosition(0, 0);
	layer->addChild(mapA, 1);
	map.push_back(mapA);
	auto mapB = TMXTiledMap::create("image/Environment/mapB.tmx");
	mapB->setName("map");
	mapB->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	mapB->setPosition(mapA->getContentSize().width, 1000);
	layer->addChild(mapB, 1);
	map.push_back(mapB);
	auto mapC = TMXTiledMap::create("image/Environment/mapC.tmx");
	mapC->setName("map");
	mapC->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	mapC->setPosition(mapB->getContentSize().width, 1000);
	layer->addChild(mapC, 1);
	map.push_back(mapC);

	nowMap = mapA;
	nextMap = mapB;

	enemyNow = EnemyCreate::create();
	enemyNow->setName("EnemyCreate");
	layer->addChild(enemyNow, 2);
	itemNow = ItemCreate::create();
	layer->addChild(itemNow, 2);

	enemyNext = EnemyCreate::create();
	layer->addChild(enemyNext, 2);
	itemNext = ItemCreate::create();
	layer->addChild(itemNext, 2);

	this->layer = layer;
	this->scheduleUpdate();
}

void MapCreate::update(float flam)
{
	if (director->getRunningScene()->getName() != "Game")
	{
		return;
	}
	if ((director->getRunningScene()->getDefaultCamera()->getPosition().x > nextMap->getPosition().x + PL_SIZE_X / 2) && setMapFlag)
	{
		//Collision用オフセット
		mapSize.width += nowMap->getMapSize().width;
		//背景AとBの変数を入れ替える
		auto s = nextMap;
		nextMap = nowMap;
		nowMap = s;
		setMapFlag = false;
	}
	if (director->getRunningScene()->getDefaultCamera()->getPosition().x > nowMap->getPosition().x + (director->getVisibleSize().width / 2) && !setMapFlag)
	{
		//次のマップを決める
		while (10)
		{
			nextMap = map[cocos2d::random(0, (int)(map.size() - 1))];
			if (nowMap != nextMap)
			{
				break;
			}
		}
		nextMap->setPosition(nowMap->getPositionX() + nowMap->getContentSize().width, 0);
		//次のマップのアイテム等配置しなおし
		ReCreate(nextMap, layer);
		setMapFlag = true;
	}
}

cocos2d::TMXTiledMap * MapCreate::GetMap()
{
	nowMap->setName("map");
	return nowMap;
}

cocos2d::TMXTiledMap * MapCreate::GetNextMap()
{
	return nextMap;
}

cocos2d::Size MapCreate::GetMapSize()
{
	return mapSize;
}

EnemyCreate * MapCreate::GetEnemyCt()
{
	return enemyNow;
}

ItemCreate * MapCreate::GetItemCt()
{
	return itemNow;
}

bool MapCreate::GetMapSetFlag()
{
	return setMapFlag;
}

void MapCreate::ReCreate(cocos2d::TMXTiledMap * map, cocos2d::Layer* layer)
{
	itemNow->ClearList();
	enemyNow->ClearList();
	for (int y = 0; y < map->getMapSize().height; y++)
	{
		for (int x = 0; x < map->getMapSize().width; x++)
		{
			auto lay = map->getLayer("ground");
			auto tile = lay->getTileGIDAt(cocos2d::Vec2(x, y));
			if (tile)
			{
				auto properties = map->getPropertiesForGID(tile).asValueMap();
				if (properties.at("col").asInt() == 2)
				{
					//敵スポーン座標
					enemyNow->AddCreateList(map, Vec2(x, y));
				}
				else
				{
					itemNow->AddCreateList(map, Vec2(x, y), properties.at("col").asInt());
				}
			}
		}
	}
	//リストをもとに配置
	enemyNow->Push(layer);
	itemNow->Push(layer);
}

void MapCreate::NextSet()
{

}
