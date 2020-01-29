#include "Jumping.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "CheckCollision.h"

USING_NS_CC;

//�W�����v����
bool Jumping::operator()(cocos2d::Sprite & sp, actModule & module)
{
	//Player��Enemy�����Ƃ��날��̂Őe�N���X�����proteceted�Ȃǂł܂Ƃ߂�
	auto unit = static_cast<Unit*>(module.sprite);
	//�V��ɓ������Ă���
	module.offset = { 0, 0 };
	if (!CheckCollision()(*module.sprite, module))
	{
		unit->SetActState(ACT::FALL);
		return false;
	}
	//0�ȏ�ł���Ώd�͉����x�������Ă���
	if (unit->GetJumpSpeed() >= module.jumpHeight)
	{
		unit->SetJumpSpeed(unit->GetJumpSpeed() - module.gravity);
	}
	else
	{
		unit->SetActState(ACT::FALL);
		return false;
	}
	//sp.setPosition(sp.getPosition().x + module.velocity.x, sp.getPosition().y + (module.velocity.y + unit->GetJumpSpeed()));
	return true;
}
