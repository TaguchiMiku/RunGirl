#include "AttackMove.h"
#include "obj/Player.h"
#include "CheckCollision.h"

USING_NS_CC;

bool AttackMove::operator()(cocos2d::Sprite & sp, actModule & module)
{
	//sp.setPosition(sp.getPosition().x + module.velocity.x, sp.getPosition().y);
	//sp.runAction(FlipX::create(module.reverce));
	return false;
}
