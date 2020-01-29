#include "FallMove.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "CheckCollision.h"

USING_NS_CC;

//d—Í—‰º‰‘¬İ’è
bool FallMove::operator()(cocos2d::Sprite& sp, actModule& module)
{
	auto unit = static_cast<Unit*>(module.sprite);
	if (unit->GetJumpSpeed() <= module.jumpHeight)
	{
		//0‚É‚·‚é
		unit->SetJumpSpeed(module.jumpHeight);
	}
	return true;
}
