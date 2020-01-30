#include "Attack.h"
#include "Animation/AnimCtl.h"

Attack * Attack::createAttack()
{
	return Attack::create();
}

Attack::Attack()
{
}

Attack::~Attack()
{
}

void Attack::Init(cocos2d::Vec2 position, cocos2d::Vec2 scale, cocos2d::Layer * layer)
{
	lpAnimCtl.AddAnimation("Fx", "impact", 0.05f);
	setPosition(position);
	this->setName("Attack");
	layer->addChild(this, 1);
}
