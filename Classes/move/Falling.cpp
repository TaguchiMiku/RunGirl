#include "Falling.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "CheckCollision.h"
#include "debug/_DebugConOut.h"

USING_NS_CC;

//��������
bool Falling::operator()(actModule & module)
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
	if (!CheckCollision()(module))
	{
		auto director = cocos2d::Director::getInstance();
		auto map = (cocos2d::TMXTiledMap*)director->getRunningScene()->getChildByName("BG_BACKGROUND")->getChildByName("map");
		module.sprite->setPositionY(floor(module.sprite->getPosition().y) - ((int)(floor(module.sprite->getPosition().y) - module.sprite->getContentSize().height / 2.0f) % (int)map->getTileSize().height));
		unit->SetActState(ACT::IDLE);
		return false;
	}
	module.sprite->setPositionY(module.sprite->getPosition().y + module.velocity.y);
	return true;
}
