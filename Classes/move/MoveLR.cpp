#include "MoveLR.h"
#include "effect/EffectMng.h"
#include "obj/Player.h"
#include "CheckCollision.h"

USING_NS_CC;

bool MoveLR::operator()(cocos2d::Sprite& sp, actModule& module)
{
	module.velocity.x = floor(static_cast<Unit*>(module.sprite)->GetVelocityX());
	if (CheckCollision()(*module.sprite, module))
	{
		sp.setPositionX(floor(sp.getPosition().x + module.velocity.x));
	}
	sp.runAction(FlipX::create(module.reverce));
	return true;
}
