#include "Jumping.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "CheckCollision.h"

USING_NS_CC;

//ƒWƒƒƒ“ƒvˆ—
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
	//“Vˆä‚É“–‚½‚Á‚Ä‚¢‚é
	if (!CheckCollision()(*module.sprite, module))
	{
		unit->SetJumpSpeed(0);
		unit->SetActState(ACT::FALL);
		return false;
	}
	sp.setPosition(sp.getPosition().x + module.velocity.x, sp.getPosition().y + module.velocity.y);
	return true;
}
