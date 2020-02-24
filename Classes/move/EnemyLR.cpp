#include "EnemyLR.h"
#include "obj/Player.h"

USING_NS_CC;

bool EnemyLR::operator()(actModule& module)
{
	module.sprite->setPosition(module.sprite->getPosition().x + module.velocity.x, module.sprite->getPosition().y + module.velocity.y);
	module.sprite->runAction(FlipX::create(module.reverce));
	return true;
}