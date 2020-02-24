#include "FallMove.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "CheckCollision.h"

USING_NS_CC;

//�d�͗��������ݒ�
bool FallMove::operator()(actModule& module)
{
	auto unit = static_cast<Unit*>(module.sprite);
	if ((unit->GetJumpSpeed() <= module.jumpHeight))
	{
		//���Z�b�g����
		unit->SetJumpSpeed(module.jumpHeight);
	}
	return true;
}
