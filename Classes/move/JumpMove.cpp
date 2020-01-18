#include "JumpMove.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "CheckCollision.h"
//#include "sound/SoundMng.h"

USING_NS_CC;

//ƒWƒƒƒ“ƒv‚Ì‰‘¬“xÝ’è
bool JumpMove::operator()(cocos2d::Sprite& sp, actModule& module)
{
	//lpSoundMng.OnceSoundPlay("Resources/sound/jump2.ckb");
	if (module.sprite->getName() == "Player")
	{
		auto player = static_cast<Player*>(module.sprite);
		player->SetJumpSpeed(module.jumpHeight);
	}
	if (module.sprite->getName() == "Enemy")
	{
		auto enemy = static_cast<Enemy*>(module.sprite);
		enemy->SetJumpSpeed(module.jumpHeight);
	}
	return true;
}
