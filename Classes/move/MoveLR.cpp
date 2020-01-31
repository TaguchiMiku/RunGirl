#include "MoveLR.h"
#include "effect/EffectMng.h"
#include "obj/Player.h"

USING_NS_CC;

bool MoveLR::operator()(cocos2d::Sprite& sp, actModule& module)
{
	sp.setPositionX(sp.getPosition().x + module.velocity.x/*, sp.getPosition().y + module.velocity.y*/);
	sp.runAction(FlipX::create(module.reverce));
	return true;
}
