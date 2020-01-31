#include "EnemyLR.h"
#include "obj/Player.h"

USING_NS_CC;

bool EnemyLR::operator()(cocos2d::Sprite& sp, actModule& module)
{
	sp.setPosition(sp.getPosition().x + module.velocity.x, sp.getPosition().y + module.velocity.y);
	sp.runAction(FlipX::create(module.reverce));
	return true;
}