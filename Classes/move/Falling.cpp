#include "Falling.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "CheckCollision.h"
#include "debug/_DebugConOut.h"

USING_NS_CC;

//��������
bool Falling::operator()(cocos2d::Sprite & sp, actModule & module)
{
	//�󒆂ɂ������ɗ���������
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

	//�n�ʂƓ��������痎�����Ȃ�	
	if (!CheckCollision()(sp, module))
	{
		auto director = cocos2d::Director::getInstance();
		auto map = (cocos2d::TMXTiledMap*)director->getRunningScene()->getChildByName("BG_BACKGROUND")->getChildByName("map");
		sp.setPositionY(floor(sp.getPosition().y) - ((int)(floor(sp.getPosition().y) - sp.getContentSize().height / 2) % (int)map->getTileSize().height));
		unit->SetActState(ACT::IDLE);
		return false;
	}
	sp.setPositionY(sp.getPosition().y + module.velocity.y);
	return true;
}
