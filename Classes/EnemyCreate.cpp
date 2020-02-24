#include "EnemyCreate.h"
#include "obj/Enemy.h"
#include "obj/Player.h"
#include "Score.h"
#define EN_CHAR_SIZE 30.0f

USING_NS_CC;

EnemyCreate::EnemyCreate()
{
}

EnemyCreate::~EnemyCreate()
{
}

EnemyCreate * EnemyCreate::createEnemyC()
{
	return EnemyCreate::create();
}

void EnemyCreate::AddCreateList(cocos2d::TMXTiledMap * map, cocos2d::Vec2 tile)
{
	//�G�X�|�[�����W
	sponeList.push_back(
		Vec2(map->getPosition().x + tile.x * map->getTileSize().width,
			 (map->getTileSize().height + EN_CHAR_SIZE / 2.0f) * (map->getMapSize().height - 1.0f - tile.y))
	);
}

void EnemyCreate::Push(Layer* layer)
{
	//�G�̒ǉ�
	for (auto list : sponeList)
	{
		//Enemy�ǉ�
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
			if (player->getPosition().x - ene->getPosition().x > 1000.0f)
			{
				ene->SetDeathFlag(true);
			}
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
			return true;
		}
		return false;
	});
	enSpList.erase(death, enSpList.end());
}

void EnemyCreate::ClearList()
{
	sponeList.clear();
}

std::vector<Enemy*> EnemyCreate::GetEnSpriteList()
{
	return enSpList;
}
