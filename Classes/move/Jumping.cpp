#include "Jumping.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "CheckCollision.h"

USING_NS_CC;

//ジャンプ処理
bool Jumping::operator()(cocos2d::Sprite & sp, actModule & module)
{
	//PlayerとEnemy同じところあるので親クラスを作りprotecetedなどでまとめる
	auto unit = static_cast<Unit*>(module.sprite);
	//天井に当たっている
	module.offset = { 0, 0 };
	if (!CheckCollision()(*module.sprite, module))
	{
		unit->SetActState(ACT::FALL);
		return false;
	}
	//0以上であれば重力加速度を引いていく
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
