#include "Jumping.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "CheckCollision.h"

USING_NS_CC;

//ジャンプ処理
bool Jumping::operator()(cocos2d::Sprite & sp, actModule & module)
{
	auto unit = static_cast<Unit*>(module.sprite);
	if (unit->GetJumpSpeed() > -module.jumpHeight)
	{
		unit->SetJumpSpeed(unit->GetJumpSpeed() + module.gravity);
	}
	else
	{
		unit->SetActState(ACT::FALL);
		return false;
	}
	module.velocity.y = unit->GetJumpSpeed();
	//天井に当たっている
	if (!CheckCollision()(*module.sprite, module))
	{
		unit->SetJumpSpeed(0);
		unit->SetActState(ACT::FALL);
		return false;
	}
	sp.setPositionY(sp.getPosition().y + module.velocity.y);
	return true;
}
