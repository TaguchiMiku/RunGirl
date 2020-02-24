#include "Jumping.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "CheckCollision.h"

USING_NS_CC;

//�W�����v����
bool Jumping::operator()(actModule & module)
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
	if (!CheckCollision()(module))
	{
		unit->SetJumpSpeed(0);
		unit->SetActState(ACT::FALL);
		return false;
	}
	module.sprite->setPositionY(module.sprite->getPosition().y + module.velocity.y);
	return true;
}
