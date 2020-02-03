#include "ActionCtl.h"
#include "obj/Player.h"
#include "move/MoveLR.h"
#include "move/FallMove.h"
#include "move/JumpMove.h"
#include "move/Jumping.h"
#include "move/Falling.h"
#include "move/AttackMove.h"
#include "move/EnemyLR.h"
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
	unit = nullptr;
}


ActionCtl::~ActionCtl()
{
}

bool ActionCtl::AddModule(std::string str, actModule& module)
{
	mapAct.emplace(str, std::move(module));
	if (str == "右移動")
	{
		mapAct[str].act.emplace_back(CheckCollision());
		mapAct[str].act.emplace_back(CheckList());
		mapAct[str].runAction = MoveLR();
	}
	if (str == "左移動")
	{
		mapAct[str].act.emplace_back(CheckCollision());
		mapAct[str].act.emplace_back(CheckList());
		mapAct[str].act.emplace_back(CheckKey());
		mapAct[str].runAction = EnemyLR();
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

void ActionCtl::MoveModule(input_data data, float delta)
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
				return rtnFlg;
			}
		}
		return rtnFlg;
	};
	
	//mapに登録しているアクション分回す
	if (unit != nullptr)
	{
		if (unit->GetAttackFlag())
		{
			if (unit->getNumberOfRunningActionsByTag(static_cast<int>(ACT_TAG::ATTACK)) <= 0)
			{
				unit->stopAllActions();
				unit->SetAttackFlag(false);
			}
		}	
	}

	for (auto map : mapAct)
	{
		map.second.nowKey = data.key.first;
		map.second.oldKey = data.key.second;
		unit = static_cast<Unit*>(map.second.sprite);
		if (CheckModule(map.second))
		{
			if(!unit->GetAttackFlag())
			{
				if (map.second.animName != animName)
				{
					if (plNowAct != nullptr)
					{
						map.second.sprite->stopAllActions();
					}
					plNowAct = lpAnimCtl.RunAnimation(map.second.sprite, map.second.animName, -1, static_cast<int>(ACT_TAG::NORMAL));
					animName = map.second.animName;
				}
				if ((unit->GetActState() == ACT::IDLE && map.second.action == ACT::RIGHT) || (map.second.action != ACT::RIGHT))
				{
					//現在の状態は落下中に攻撃すると落下しなくなる処理である
					//右移動するのはIDLEか右移動のときでそれ以外は移動しないようにする必要がある
					unit->SetActState(map.second.action);
				}
			}
			map.second.runAction(*map.second.sprite, map.second);
			// 上記でattackFlagが書き換わるため、もう一度判断して処理する
			if (unit->GetAttackFlag())
			{
				if (unit->getNumberOfRunningActionsByTag(static_cast<int>(ACT_TAG::ATTACK)) > 0)
				{
					return;
				}
				if ((map.second.animName == "player-attack" && animName == "player-run") || (animName != "player-attack"))
				{
					if (plNowAct != nullptr)
					{
						map.second.sprite->stopAllActions();
					}
				}
				if (map.first == "攻撃")
				{
					plNowAct = lpAnimCtl.RunAnimation(map.second.sprite, map.second.animName, 1, static_cast<int>(ACT_TAG::ATTACK));
					animName = map.second.animName;
				}
			}
		}
	}
}