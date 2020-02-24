#include "MoveLR.h"
#include "effect/EffectMng.h"
#include "obj/Player.h"
#include "CheckCollision.h"

USING_NS_CC;

bool MoveLR::operator()(actModule& module)
{
	module.velocity.x = floor(static_cast<Unit*>(module.sprite)->GetVelocityX());
	if (CheckCollision()(module))
	{
		module.sprite->setPositionX(floor(module.sprite->getPosition().x + module.velocity.x));
	}
	module.sprite->runAction(FlipX::create(module.reverce));
	return true;
}
