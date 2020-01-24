#include "EnemyCreate.h"
#include "obj/Enemy.h"
#include "obj/Player.h"
#include "ui/Attack.h"
#include "Score.h"
#include "debug/_DebugConOut.h"


USING_NS_CC;

EnemyCreate * EnemyCreate::createEnemyC()
{
	return EnemyCreate::create();
}

EnemyCreate::EnemyCreate()
{
	listCnt = 0;
	onceFlag = true;
}

EnemyCreate::~EnemyCreate()
{
}

void EnemyCreate::AddCreateList(cocos2d::TMXTiledMap * map, cocos2d::Vec2 tile)
{
	//“GƒXƒ|[ƒ“À•W
	sponeList.push_back(Vec2(map->getPosition().x + tile.x * map->getTileSize().width, (map->getMapSize().height - 1 - tile.y) * map->getTileSize().height + 100));
}

void EnemyCreate::Push(Layer* layer)
{
	//“G‚Ì’Ç‰Á
	for (auto list : sponeList)
	{
		//Enemy’Ç‰Á
		auto enemy = Enemy::createEnemy();
		enemy->setPosition(list);
		layer->addChild(enemy, 2);
		sponeSpList.push_back(enemy);
	}
}

void EnemyCreate::Update(float flam, Player* player, Attack* attack, Score* score)
{
	plRect = player->getBoundingBox();
	listCnt = 0;
	if (player != nullptr && sponeSpList.size() > 0)
	{
		onceFlag = true;
		for (auto ene : sponeSpList)
		{
			auto eneRect = ene->getBoundingBox();
			auto atkRect = attack->getBoundingBox();
			if (plRect.intersectsRect(eneRect))
			{
				if (player->GetAttackFlag())
				{
					TRACE("Destroy_Enemy\n");
					//UŒ‚Žž‚É“G‚É“–‚½‚Á‚½‚çŽ€–Sƒtƒ‰ƒO‚ð—§‚Ä‚é
					sponeSpList.at(listCnt)->SetDeathFlag(true);				
					score->AddScore(100);
					attack->setPosition(Vec2(player->getPosition().x + 50, player->getPosition().y));
					lpAnimCtl.RunAnimation(attack, "Fx-impact", 1);
					player->SetAttackFlag(false);
					break;
				}
				if (ene == collSpr)
				{
					//“G‚Æ“–‚½‚è‘±‚¯‚Ä‚¢‚½‚çfalse‚É‚µ‚ÄHP‚ÌŒ¸‚ç‚µ‚ð‚È‚­‚·
					onceFlag = false;
				}
				if (onceFlag && player->GetActState() != ACT::ATTACK)
				{
					collSpr = ene;
					//lpSoundMng.OnceSoundPlay("Resources/sound/die.ckb");
					onceFlag = false;
					score->AddScore(-10);
					player->SetActState(ACT::DIE);
				}
				break;
			}
			listCnt++;
		}
		DeathCheck();
	}
}

void EnemyCreate::DeathCheck()
{
	auto death = std::remove_if(sponeSpList.begin(), sponeSpList.end(), 
		[](Enemy* enemy) { 
		if (enemy->GetDeathFlag())
		{
			enemy->removeFromParentAndCleanup(true);
		}
		return enemy->GetDeathFlag();
	});
	sponeSpList.erase(death, sponeSpList.end());
}

void EnemyCreate::ClearList()
{
	sponeList.clear();
	sponeSpList.clear();
}
