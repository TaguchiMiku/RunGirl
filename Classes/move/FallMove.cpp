#include "FallMove.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "CheckCollision.h"

USING_NS_CC;

//重力落下初速設定
bool FallMove::operator()(actModule& module)
{
	auto unit = static_cast<Unit*>(module.sprite);
	if ((unit->GetJumpSpeed() <= module.jumpHeight))
	{
		//リセットする
		unit->SetJumpSpeed(module.jumpHeight);
	}
	return true;
}
