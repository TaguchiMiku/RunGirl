#include "MapCreate.h"

USING_NS_CC;

cocos2d::Node * MapCreate::createMap()
{
	return MapCreate::create();
}

MapCreate::MapCreate()
{
}

MapCreate::~MapCreate()
{
}

void MapCreate::Init(cocos2d::Layer * layer)
{
	mapA = TMXTiledMap::create("image/Environment/test.tmx");
	mapA->setName("map");
	mapA->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	mapA->setPosition(0, 0);
	layer->addChild(mapA, 1);
	mapB = TMXTiledMap::create("image/Environment/test2.tmx");
	mapB->setName("map");
	mapB->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	mapB->setPosition(mapA->getContentSize().width, 0);
	layer->addChild(mapB, 1);
	this->scheduleUpdate();
}

void MapCreate::update(float flam)
{
	if (Director::getInstance()->getRunningScene()->getName() != "Game")
	{
		return;
	}
	
	if (Director::getInstance()->getRunningScene()->getDefaultCamera()->getPosition().x + mapB->getTileSize().width > mapB->getPosition().x)
	{
		//�w�iA����ʍ��O�ɏo�������ꍇ�A�w�iA��w�iB�̉E�ׂɈڂ�
		mapA->setPositionX(mapB->getPositionX() + mapB->getContentSize().width);

		//�w�iA��B�̕ϐ������ւ���
		auto s = mapB;
		mapB = mapA;
		mapA = s;
		mapA->setName("map");
	}
}

cocos2d::TMXTiledMap * MapCreate::GetMap()
{
	return mapA;
}
