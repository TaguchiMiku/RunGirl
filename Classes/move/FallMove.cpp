#include "FallMove.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "CheckCollision.h"

USING_NS_CC;

//重力落下初速設定
bool FallMove::operator()(cocos2d::Sprite& sp, actModule& module)
{
	auto unit = static_cast<Unit*>(module.sprite);
	if (unit->GetJumpSpeed() <= module.jumpHeight)
	{
		//0にする
		unit->SetJumpSpeed(module.jumpHeight);
	}
	return true;
}
