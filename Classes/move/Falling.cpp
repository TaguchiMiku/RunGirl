#include "Falling.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "CheckCollision.h"

USING_NS_CC;

//—‰ºˆ—
bool Falling::operator()(cocos2d::Sprite & sp, actModule & module)
{
	//‹ó’†‚É‚¢‚½‚çí‚É—‰º‚³‚¹‚é
	auto unit = static_cast<Unit*>(module.sprite);
	if (unit->GetJumpSpeed() <= module.jumpHeight)
	{
		unit->SetJumpSpeed(unit->GetJumpSpeed() + module.gravity);
	}
	module.velocity.y -= unit->GetJumpSpeed();

	//’n–Ê‚Æ“–‚½‚Á‚½‚ç—‰º‚µ‚È‚¢
	if (!CheckCollision()(*module.sprite, module))
	{
		auto director = cocos2d::Director::getInstance();
		auto map = (cocos2d::TMXTiledMap*)director->getRunningScene()->getChildByName("BG_BACKGROUND")->getChildByName("map");
		double mass = floor((module.sprite->getPosition().y - 29) / map->getTileSize().height);
		auto diff = (module.sprite->getPosition().y - 29) - (mass * map->getTileSize().height);
		module.sprite->setPosition(module.sprite->getPosition().x, module.sprite->getPosition().y + diff);
		module.velocity.y = 0;
	}
	sp.setPosition(sp.getPosition().x + module.velocity.x, sp.getPosition().y + module.velocity.y);
	module.sprite->runAction(cocos2d::MoveBy::create(0.0f, Vec2(module.velocity.x, module.velocity.y)));	
	return true;
}
