#include "Falling.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "CheckCollision.h"

USING_NS_CC;

//落下処理
bool Falling::operator()(cocos2d::Sprite & sp, actModule & module)
{
	//空中にいたら常に落下させる
	auto unit = static_cast<Unit*>(module.sprite);
	if (unit->GetJumpSpeed() > -module.jumpHeight)
	{
		unit->SetJumpSpeed(unit->GetJumpSpeed() + module.gravity);
	}
	else
	{
		unit->SetJumpSpeed(-module.jumpHeight);
	}
	module.velocity.y = unit->GetJumpSpeed();

	//地面と当たったら落下しない	
	if (!CheckCollision()(sp, module))
	{
		auto director = cocos2d::Director::getInstance();
		auto map = (cocos2d::TMXTiledMap*)director->getRunningScene()->getChildByName("BG_BACKGROUND")->getChildByName("map");
		sp.setPositionY(floor(sp.getPosition().y) - ((int)(floor(sp.getPosition().y) - sp.getContentSize().height / 2) % (int)map->getTileSize().height));
		unit->SetActState(ACT::IDLE);
		return false;
	}
	sp.setPosition(sp.getPosition() + module.velocity);
	return true;
}
