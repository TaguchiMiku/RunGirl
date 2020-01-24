#include "MapCreate.h"
#include "obj/Enemy.h"
#include "item/HpItem.h"
#include "item/NormalItem.h"
#include "EnemyCreate.h"
#include "ItemCreate.h"
USING_NS_CC;

cocos2d::Node * MapCreate::createMap()
{
	return MapCreate::create();
}

MapCreate::MapCreate()
{
	mapSize = Vec2(0, 0);
	setMapFlag = true;
}

MapCreate::~MapCreate()
{
}

void MapCreate::Init(cocos2d::Layer * layer)
{
	director = Director::getInstance();
	auto mapA = TMXTiledMap::create("image/Environment/test.tmx");
	mapA->setName("map");
	mapA->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	mapA->setPosition(0, 0);
	layer->addChild(mapA, 1);
	map.push_back(mapA);
	auto mapB = TMXTiledMap::create("image/Environment/test2.tmx");
	mapB->setName("map");
	mapB->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	mapB->setPosition(mapA->getContentSize().width, 0);
	layer->addChild(mapB, 1);
	map.push_back(mapB);

	nowMap = mapA;
	nextMap = mapB;

	enemyCt = EnemyCreate::create();
	layer->addChild(enemyCt, 2);
	itemCt = ItemCreate::create();
	layer->addChild(itemCt, 2);
	this->layer = layer;
	this->scheduleUpdate();
}

void MapCreate::update(float flam)
{
	if (director->getRunningScene()->getName() != "Game")
	{
		return;
	}
	
	if (director->getRunningScene()->getDefaultCamera()->getPosition().x + nextMap->getTileSize().width > nextMap->getPosition().x && setMapFlag)
	{
		//次のマップのアイテム等配置しなおし
		ReCreate(nextMap, layer);
		//Collision用オフセット
		mapSize.width += nowMap->getMapSize().width;
		//背景AとBの変数を入れ替える
		auto s = nextMap;
		nextMap = nowMap;
		nowMap = s;
		setMapFlag = false;
	}
	if (director->getRunningScene()->getDefaultCamera()->getPosition().x > nowMap->getPosition().x + director->getVisibleSize().width / 2)
	{
		//カメラが背景Aを完全に出たら、背景Aを背景Bの右隣に移す
		while (10)
		{
			nextMap = map[cocos2d::random(0, (int)(map.size() - 1))];
			if (nowMap != nextMap)
			{
				break;
			}
		}
		nextMap->setPositionX(nowMap->getPositionX() + nowMap->getContentSize().width);
		setMapFlag = true;
	}
}

cocos2d::TMXTiledMap * MapCreate::GetMap()
{
	nowMap->setName("map");
	return nowMap;
}

cocos2d::Size MapCreate::GetMapSize()
{
	return mapSize;
}

EnemyCreate * MapCreate::GetEnemyCt()
{
	return enemyCt;
}

ItemCreate * MapCreate::GetItemCt()
{
	return itemCt;
}

void MapCreate::ReCreate(cocos2d::TMXTiledMap * map, cocos2d::Layer* layer)
{
	enemyCt->ClearList();
	itemCt->ClearList();
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
					enemyCt->AddCreateList(map, Vec2(x, y));
				}
				else
				{
					itemCt->AddCreateList(map, Vec2(x, y), properties.at("col").asInt());
				}
			}
		}
	}
	//リストをもとに配置
	enemyCt->Push(layer);
	itemCt->Push(layer);
}
