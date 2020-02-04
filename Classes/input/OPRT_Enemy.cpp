#include "OPRT_Enemy.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "ui/Attack.h"
#include "Score.h"
#include "CheckCollision.h"
#include "sound/SoundMng.h"
#define START_MOVE_DISTANCE 500		// “G‚ª“®‚­‚Æ”»’f‚·‚éƒvƒŒƒCƒ„[‚Æ‚Ì‹——£

USING_NS_CC;

OPRT_Enemy::OPRT_Enemy()
{
}

OPRT_Enemy::OPRT_Enemy(Unit * unit)
{
	jumpFlag = false;
	this->unit = unit;
}

OPRT_Enemy::~OPRT_Enemy()
{
}

void OPRT_Enemy::Update()
{
	auto director = Director::getInstance();
	auto player = static_cast<Player*>(director->getRunningScene()->getChildByName("plLayer")->getChildByName("Player"));
	auto attack = static_cast<Attack*>(director->getRunningScene()->getChildByName("plLayer")->getChildByName("Attack"));
	auto score = static_cast<Score*>(director->getRunningScene()->getChildByName("Score"));
	auto enemy = static_cast<Enemy*>(unit);
	plRect = player->getBoundingBox();
	enRect = enemy->getBoundingBox();

	if (plRect.intersectsRect(enRect))
	{
		if (player->GetAttackFlag())
		{
			//UŒ‚Žž‚É“G‚É“–‚½‚Á‚½‚çŽ€–Sƒtƒ‰ƒO‚ð—§‚Ä‚é
			if (!enemy->GetDeathFlag())
			{
				//lpSoundMng.OnceSoundPlay("enemy_die.ckb")
			}
			enemy->SetDeathFlag(true);
			score->AddScore(100);
			attack->setPosition(Vec2(player->getPosition().x + 50, player->getPosition().y));
			lpAnimCtl.RunAnimation(attack, "Fx-impact", 1, 0);
		}
		else
		{
			score->AddScore(-10);
			player->SetSlowlyFlag(true);
		}
	}

	//ƒWƒƒƒ“ƒv
	actModule actLeft;
	actLeft.velocity = Vec2(-5, 0);
	actLeft.sprite = enemy;
	actLeft.offset.emplace_back(Vec2(-30, 15));
	actLeft.offset.emplace_back(Vec2(-30, -14));
	if (!CheckCollision()(*enemy, actLeft) && enemy->GetActState() == ACT::LEFT)
	{
		jumpFlag = true;
	}

	data.key.second = data.key.first;
	if (jumpFlag)
	{
		data.key.first = EventKeyboard::KeyCode::KEY_A;
		jumpFlag = false;
	}
	else if((enemy->getPosition().x - player->getPosition().x) < START_MOVE_DISTANCE)
	{
		data.key.first = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
	}
	else
	{
		data.key.first = EventKeyboard::KeyCode::KEY_NONE;
	}
}
