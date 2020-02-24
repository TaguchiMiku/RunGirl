#include "JumpMove.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "CheckCollision.h"
//#include "sound/SoundMng.h"

USING_NS_CC;

//ƒWƒƒƒ“ƒv‚Ì‰‘¬“xİ’è
bool JumpMove::operator()(actModule& module)
{
	auto unit = static_cast<Unit*>(module.sprite);
	unit->SetJumpSpeed(module.jumpHeight);
	return true;
}
