#include "FallMove.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "CheckCollision.h"

USING_NS_CC;

//�d�͗��������ݒ�
bool FallMove::operator()(cocos2d::Sprite& sp, actModule& module)
{
	if (module.sprite->getName() == "Player")
	{
		auto player = static_cast<Player*>(module.sprite);
		if (player->GetJumpSpeed() <= module.jumpHeight)
		{
			//0�ɂ���
			player->SetJumpSpeed(module.jumpHeight);
		}
	}
	if (module.sprite->getName() == "Enemy")
	{
		auto enemy = static_cast<Enemy*>(module.sprite);
		if (enemy->GetJumpSpeed() <= module.jumpHeight)
		{
			//0�ɂ���
			enemy->SetJumpSpeed(module.jumpHeight);
		}
	}
	return true;
}
