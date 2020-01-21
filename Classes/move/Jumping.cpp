#include "Jumping.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "CheckCollision.h"

USING_NS_CC;

//�W�����v����
bool Jumping::operator()(cocos2d::Sprite & sp, actModule & module)
{
	if (module.sprite->getName() == "Player")
	{
		auto player = static_cast<Player*>(module.sprite);
		//�V��ɓ������Ă���
		module.offset = { 0, 0 };
		if (!CheckCollision()(*module.sprite, module))
		{
			player->SetActState(ACT::FALL);
			return false;
		}
		//0�ȏ�ł���Ώd�͉����x�������Ă���
		if (player->GetJumpSpeed() >= module.jumpHeight)
		{
			player->SetJumpSpeed(player->GetJumpSpeed() - module.gravity);
		}
		else
		{
			player->SetActState(ACT::FALL);
			return false;
		}
		sp.setPosition(sp.getPosition().x + module.velocity.x, sp.getPosition().y + (module.velocity.y + player->GetJumpSpeed()));
	}

	//if (module.sprite->getName() == "Enemy")
	//{
	//	auto enemy = static_cast<Enemy*>(module.sprite);
	//	//0�ȏ�ł���Ώd�͉����x�������Ă���
	//	if (enemy->GetJumpSpeed() >= module.jumpHeight)
	//	{
	//		enemy->SetJumpSpeed(enemy->GetJumpSpeed() - module.gravity);
	//	}
	//	else
	//	{
	//		enemy->SetActState(ACT::FALL);
	//	}
	//	sp.setPosition(sp.getPosition().x + module.velocity.x, sp.getPosition().y + (module.velocity.y + enemy->GetJumpSpeed()));
	//}
	return true;
}
