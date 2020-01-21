#include "ActionCtl.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "move/MoveLR.h"
#include "move/FallMove.h"
#include "move/JumpMove.h"
#include "move/Jumping.h"
#include "move/Falling.h"
#include "move/AttackMove.h"
#include "CheckKey.h"
#include "CheckList.h"
#include "CheckCollision.h"
//#include "debug/_DebugConOut.h"
#pragma execution_charactor_set("utf-8");

USING_NS_CC;

ActionCtl::ActionCtl()
{
	animName = "player-idle";
	plNowAct = nullptr;
	enNowAct = nullptr;
}


ActionCtl::~ActionCtl()
{
}

bool ActionCtl::AddModule(std::string str, actModule& module)
{
	mapAct.emplace(str, std::move(module));
	if (str == "左移動" || str == "右移動")
	{
		mapAct[str].act.emplace_back(CheckCollision());
		mapAct[str].act.emplace_back(CheckList());
		mapAct[str].act.emplace_back(CheckKey());
		mapAct[str].runAction = MoveLR();
	}
	if (str == "ジャンプ")
	{
		mapAct[str].act.emplace_back(CheckList());
		mapAct[str].act.emplace_back(CheckKey());
		mapAct[str].runAction = JumpMove();
	}
	if (str == "ジャンプ中")
	{
		mapAct[str].act.emplace_back(CheckList());
		mapAct[str].runAction = Jumping();
	}
	if (str == "落下")
	{
		mapAct[str].act.emplace_back(CheckCollision());
		mapAct[str].act.emplace_back(CheckList());
		mapAct[str].runAction = FallMove();
	}
	if (str == "落下中")
	{
		mapAct[str].act.emplace_back(CheckList());
		mapAct[str].runAction = Falling();
	}
	if (str == "攻撃")
	{
		mapAct[str].act.emplace_back(CheckCollision());
		mapAct[str].act.emplace_back(CheckList());
		mapAct[str].act.emplace_back(CheckKey());
		mapAct[str].runAction = AttackMove();
	}
	return true;
}

void ActionCtl::MoveModule(input_data data)
{
	/*チェックリストを全て回しす
	  全部true		 = trueを返す
	  1つでもfalse	 = falseを返す*/
	auto CheckModule = [](actModule& module) {
		bool rtnFlg = true;
		for (auto actList : module.act)
		{
			if (!actList.operator()(*module.sprite, module))
			{
				rtnFlg = false;
			}
		}
		return rtnFlg;
	};
	
	//mapに登録しているアクション分回す
	for (auto map : mapAct)
	{
		if (map.first == "右移動" && map.second.sprite->getName() == "Player")
		{
			map.second.nowKey = cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
			map.second.oldKey = data.key.second;
		}
		else if (map.first == "左移動" && map.second.sprite->getName() == "Enemy")
		{
			map.second.nowKey = cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW;
			map.second.oldKey = data.key.second;
		}
		else
		{
			map.second.nowKey = data.key.first;
			map.second.oldKey = data.key.second;
		}
		
		if (CheckModule(map.second))
		{
			if (map.second.sprite->getName() == "Player")
			{
				player = static_cast<Player*>(map.second.sprite);
				//加速するかどうか
				if (player->GetAccelFlag())
				{
					map.second.animName = "player-run";
					map.second.velocity.x *= 2;
				}
				else if(map.first == "右移動")
				{
					map.second.animName = "player-walk";
					map.second.velocity.x /= 2;
				}

				if (map.second.action != player->GetActState())
				{
					if (plNowAct != nullptr)
					{
						map.second.sprite->stopAllActions();
					}
					//アニメーション
					if (map.first == "攻撃")
					{
						map.second.animName = "player-idle";
						player->SetAttackFlag(true);
						plNowAct = lpAnimCtl.RunAnimation(map.second.sprite, map.second.animName, 1);
					}
					else
					{
						plNowAct = lpAnimCtl.RunAnimation(map.second.sprite, map.second.animName, -1);
					}
				}
				player->SetActState(map.second.action);
				map.second.runAction(*map.second.sprite, map.second);
			}
			if (map.second.sprite->getName() == "Enemy")
			{
				enemy = static_cast<Enemy*>(map.second.sprite);
				if (map.second.action != enemy->GetActState())
				{
					if (enNowAct != nullptr)
					{
						map.second.sprite->stopAllActions();
					}
					//アニメーション
					enNowAct = lpAnimCtl.RunAnimation(map.second.sprite, map.second.animName, -1);
				}
				enemy->SetActState(map.second.action);
				map.second.runAction(*map.second.sprite, map.second);
			}		
		}
	}
}