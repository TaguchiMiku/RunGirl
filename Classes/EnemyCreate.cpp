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
	//�G�X�|�[�����W
	sponeList.push_back(Vec2(map->getPosition().x + tile.x * map->getTileSize().width, (map->getMapSize().height - 1 - tile.y) * map->getTileSize().height + 100));
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
		sponeSpList.push_back(enemy);
	}
}

void EnemyCreate::Update(float flam, Player* player, Attack* attack, Score* score)
{
	plRect = player->getBoundingBox();
	if (player != nullptr && sponeSpList.size() > 0)
	{
		onceFlag = true;
		//sponeSpList��enemySpList

		for (auto ene : sponeSpList)
		{
			ene->Update(flam);
			auto eneRect = ene->getBoundingBox();
			auto atkRect = attack->getBoundingBox();
			if (plRect.intersectsRect(eneRect))
			{
				if (player->GetAttackFlag())
				{
					TRACE("Destroy_Enemy\n");
					//�U�����ɓG�ɓ��������玀�S�t���O�𗧂Ă�
					ene->SetDeathFlag(true);				
					score->AddScore(100);
					attack->setPosition(Vec2(player->getPosition().x + 50, player->getPosition().y));
					lpAnimCtl.RunAnimation(attack, "Fx-impact", 1);
					player->SetAttackFlag(false);
					break;
				}
				if (ene == collSpr)
				{
					//2�̂����瓖���葱����
					//Enemy��Enemy�̃A�^�b�N������i�A�^�b�N����񂵂��ł��Ȃ��j
					//�G�Ɠ����葱���Ă�����false�ɂ���HP�̌��炵���Ȃ���
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
