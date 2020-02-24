#include "JumpMove.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "CheckCollision.h"
//#include "sound/SoundMng.h"

USING_NS_CC;

//ジャンプの初速度設定
bool JumpMove::operator()(actModule& module)
{
	auto unit = static_cast<Unit*>(module.sprite);
	unit->SetJumpSpeed(module.jumpHeight);
	return true;
}
