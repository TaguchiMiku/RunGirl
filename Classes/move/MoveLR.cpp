#include "MoveLR.h"
#include "effect/EffectMng.h"
#include "obj/Player.h"

USING_NS_CC;

bool MoveLR::operator()(cocos2d::Sprite& sp, actModule& module)
{
	module.velocity.x = (int)static_cast<Unit*>(module.sprite)->GetVelocityX();
	sp.setPositionX(sp.getPosition().x + module.velocity.x);
	sp.runAction(FlipX::create(module.reverce));
	return true;
}
