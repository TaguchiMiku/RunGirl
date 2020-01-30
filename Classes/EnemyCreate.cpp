#include "EnemyCreate.h"
#include "obj/Enemy.h"
#include "obj/Player.h"
#include "Score.h"
#include "debug/_DebugConOut.h"
#define EN_CHAR_SIZE 30

USING_NS_CC;

EnemyCreate * EnemyCreate::createEnemyC()
{
	return EnemyCreate::create();
}

EnemyCreate::EnemyCreate()
{
}

EnemyCreate::~EnemyCreate()
{
}

void EnemyCreate::AddCreateList(cocos2d::TMXTiledMap * map, cocos2d::Vec2 tile)
{
	//敵スポーン座標
	sponeList.push_back(Vec2(map->getPosition().x + tile.x * map->getTileSize().width, (map->getMapSize().height - 1 - tile.y) * map->getTileSize().height + EN_CHAR_SIZE / 2));
}

void EnemyCreate::Push(Layer* layer)
{
	//敵の追加
	for (auto list : sponeList)
	{
		//Enemy追加
		auto enemy = Enemy::create();
		enemy->setPosition(list);
		layer->addChild(enemy, 2);
		enSpList.push_back(enemy);
	}
}

void EnemyCreate::Update(float flam, Player* player, Score* score)
{
	plRect = player->getBoundingBox();
	if (player != nullptr && enSpList.size() > 0)
	{
		for (auto ene : enSpList)
		{
			ene->Update(flam);			
		}
		DeathCheck();
	}
}

void EnemyCreate::DeathCheck()
{
	auto death = std::remove_if(enSpList.begin(), enSpList.end(), 
		[](Enemy* enemy) { 
		if (enemy->GetDeathFlag())
		{
			enemy->removeFromParentAndCleanup(true);
		}
		return enemy->GetDeathFlag();
	});
	enSpList.erase(death, enSpList.end());
}

void EnemyCreate::ClearList()
{
	sponeList.clear();
	enSpList.clear();
}

std::vector<Enemy*> EnemyCreate::GetEnSpriteList()
{
	return enSpList;
}
