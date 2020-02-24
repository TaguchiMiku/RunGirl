#include "MapCreate.h"
#include "obj/Enemy.h"
#include "item/PointUpItem.h"
#include "item/SpeedUpItem.h"
#include "EnemyCreate.h"
#include "ItemGenerate.h"
#include "debug/_DebugConOut.h"
#define PL_SIZE_X 34.0f
USING_NS_CC;

MapCreate::MapCreate()
{
	mapSize = Vec2(0.0f, 0.0f);
	setMapFlag = false;
}

MapCreate::~MapCreate()
{
}

cocos2d::Node * MapCreate::createMap()
{
	return MapCreate::create();
}

void MapCreate::Init(cocos2d::Layer * layer)
{
	director = Director::getInstance();
	auto MapAdd = [this](std::string name, Vec2 position, Layer* layer) 
	{
		auto tileMap = TMXTiledMap::create("image/Environment/" + name + ".tmx");
		tileMap->setName("map");
		tileMap->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		tileMap->setPosition(position);
		layer->addChild(tileMap, 1);
		map.emplace(name, tileMap);
		mapName.emplace_back(name);
	};
	MapAdd("mapA", Vec2(0.0f, 0.0f), layer);
	MapAdd("mapB", Vec2(map["mapA"]->getContentSize().width, 1000.0f), layer);
	MapAdd("mapC", Vec2(map["mapB"]->getContentSize().width, 1000.0f), layer);
	MapAdd("mapD", Vec2(map["mapC"]->getContentSize().width, 1000.0f), layer);
	MapAdd("mapE", Vec2(map["mapD"]->getContentSize().width, 1000.0f), layer);
	MapAdd("mapF", Vec2(map["mapE"]->getContentSize().width, 1000.0f), layer);
	MapAdd("mapG", Vec2(map["mapF"]->getContentSize().width, 1000.0f), layer);
	MapAdd("mapH", Vec2(map["mapG"]->getContentSize().width, 1000.0f), layer);
	MapAdd("mapI", Vec2(map["mapH"]->getContentSize().width, 1000.0f), layer);
	MapAdd("mapJ", Vec2(map["mapI"]->getContentSize().width, 1000.0f), layer);
	MapAdd("mapK", Vec2(map["mapJ"]->getContentSize().width, 1000.0f), layer);
	MapAdd("mapL", Vec2(map["mapK"]->getContentSize().width, 1000.0f), layer);

	nowMap = map["mapA"];
	nextMap = map["mapB"];

	enemyNow = EnemyCreate::create();
	enemyNow->setName("EnemyCreate");
	layer->addChild(enemyNow, 2);
	itemNow = ItemGenerate::create();
	layer->addChild(itemNow, 2);

	enemyNext = EnemyCreate::create();
	layer->addChild(enemyNext, 2);
	itemNext = ItemGenerate::create();
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
	auto cameraPos = director->getRunningScene()->getDefaultCamera()->getPosition();
	auto visibleSize = director->getVisibleSize();
	auto a = nextMap->getPosition().x;
	if ((cameraPos.x > nextMap->getPosition().x) && setMapFlag)
	{
		//Collision用オフセット
		mapSize.width += nowMap->getMapSize().width;
		//背景AとBの変数を入れ替える
		auto s = nextMap;
		nextMap = nowMap;
		nowMap = s;
		setMapFlag = false;
	}
	if ((cameraPos.x > (nowMap->getPosition().x + (nowMap->getMapSize().width * nowMap->getTileSize().width)) - visibleSize.width / 2.0f) && !setMapFlag)
	{
		//次のマップを決める
		while (10)
		{
			nextMap = map[mapName.at(cocos2d::random(0, (int)(map.size() - 1)))];
			if (nowMap != nextMap)
			{
				break;
			}
		}
		nextMap->setPosition(nowMap->getPositionX() + nowMap->getContentSize().width, 0.0f);
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

ItemGenerate * MapCreate::GetItemCt()
{
	return itemNow;
}

bool MapCreate::GetMapSetFlag()
{
	return setMapFlag;
}

void MapCreate::ReCreate(cocos2d::TMXTiledMap * map, cocos2d::Layer* layer)
{
	enemyNow->ClearList();
	for (float y = 0; y < map->getMapSize().height; y++)
	{
		for (float x = 0; x < map->getMapSize().width; x++)
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
	itemNow->CreateItem(layer);
}