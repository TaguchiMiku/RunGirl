#include "AttackMove.h"
#include "obj/Player.h"
#include "CheckCollision.h"
#include "../debug/_DebugConOut.h"

USING_NS_CC;

bool AttackMove::operator()(cocos2d::Sprite & sp, actModule & module)
{
	auto unit = static_cast<Unit*>(module.sprite);
	unit->SetAttackFlag(true);
	return true;
}
