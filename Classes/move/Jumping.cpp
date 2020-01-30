#include "Jumping.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "CheckCollision.h"
#include "debug/_DebugConOut.h"

USING_NS_CC;

//�W�����v����
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
	//�V��ɓ������Ă���
	if (!CheckCollision()(*module.sprite, module))
	{
		TRACE("jumpPos = %f\n", sp.getPosition().y);
		unit->SetActState(ACT::FALL);
		return false;
	}
	sp.setPosition(sp.getPosition().x + module.velocity.x, sp.getPosition().y + module.velocity.y);
	return true;
}
