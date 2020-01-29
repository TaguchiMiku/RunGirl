#include "Falling.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "CheckCollision.h"
#include "debug/_DebugConOut.h"

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
	auto localModule = module;
	localModule.sprite->setPosition(localModule.sprite->getPosition().x, localModule.sprite->getPosition().y);

	//’n–Ê‚Æ“–‚½‚Á‚½‚ç—‰º‚µ‚È‚¢
	if (!CheckCollision()(*localModule.sprite, localModule))
	{
		auto director = cocos2d::Director::getInstance();
		auto map = (cocos2d::TMXTiledMap*)director->getRunningScene()->getChildByName("BG_BACKGROUND")->getChildByName("map");
		double mass = floor((localModule.sprite->getPosition().y - module.sprite->getContentSize().height / 2) / map->getTileSize().height);
		if (localModule.sprite->getPosition().y > (mass * map->getTileSize().height))
		{
			//sp.setPositionY((mass) * map->getTileSize().height + module.sprite->getContentSize().height / 2);
			sp.setPositionY(250);
			unit->SetActState(ACT::IDLE);
			TRACE("%f\n", sp.getPositionY());
		}
		else
		{
			sp.setPositionY(mass * map->getTileSize().height + module.sprite->getContentSize().height / 2);
		}
		return false;
	}
	sp.setPosition(sp.getPosition().x + module.velocity.x, sp.getPosition().y + module.velocity.y);
	//module.sprite->runAction(cocos2d::MoveBy::create(0.0f, Vec2(module.velocity.x, module.velocity.y)));	
	return true;
}
