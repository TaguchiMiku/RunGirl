#include "Falling.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "CheckCollision.h"


USING_NS_CC;

//落下処理
bool Falling::operator()(cocos2d::Sprite & sp, actModule & module)
{
	//空中にいたら常に落下させる
	Player* player;
	Enemy* enemy;
	if (module.sprite->getName() == "Player")
	{
		player = static_cast<Player*>(module.sprite);
		if (player->GetJumpSpeed() <= module.jumpHeight)
		{
			player->SetJumpSpeed(player->GetJumpSpeed() + module.gravity);
		}
		module.velocity.y -= player->GetJumpSpeed();
	}
	if (module.sprite->getName() == "Enemy")
	{
		enemy = static_cast<Enemy*>(module.sprite);
		if (enemy->GetJumpSpeed() <= module.jumpHeight)
		{
			enemy->SetJumpSpeed(enemy->GetJumpSpeed() + module.gravity);
		}
		module.velocity.y -= enemy->GetJumpSpeed();
	}

	//地面と当たったら落下しない
	//右下の当たり判定
	module.offset = { 25, -120 };
	if (!CheckCollision()(*module.sprite, module))
	{
		auto director = cocos2d::Director::getInstance();
		auto map = (cocos2d::TMXTiledMap*)director->getRunningScene()->getChildByName("BG_BACKGROUND")->getChildByName("map");
		//よくわからない1.6f(切りのいい数字1.0fだとマス目の真ん中で止まり、1.5fにするとちょうどマス目のデータが被ってるのかノミ運動になるので+0.1した1.6fできれいに止まった。謎。)
		double mass = floor((module.sprite->getPosition().y - module.offset.y) / map->getTileSize().height) - 1.6f;
		module.sprite->setPosition(module.sprite->getPosition().x, mass * map->getTileSize().height);
		module.velocity.y = 0;
		if (module.sprite->getName() == "Player")
		{
			player->SetActState(ACT::IDLE);
		}
		if (module.sprite->getName() == "Enemy")
		{
			enemy->SetActState(ACT::IDLE);
		}
		return false;
	}
	//左下の当たり判定
	module.offset = { -25, -120 };
	if (!CheckCollision()(*module.sprite, module))
	{
		auto director = cocos2d::Director::getInstance();
		auto map = (cocos2d::TMXTiledMap*)director->getRunningScene()->getChildByName("BG_BACKGROUND")->getChildByName("map");
		//よくわからない1.6f(切りのいい数字1.0fだとマス目の真ん中で止まり、1.5fにするとちょうどマス目のデータが被ってるのかノミ運動になるので+0.1した1.6fできれいに止まった。謎。)
		double mass = floor((module.sprite->getPosition().y - module.offset.y) / map->getTileSize().height) - 1.6f;
		module.sprite->setPosition(module.sprite->getPosition().x, mass * map->getTileSize().height);
		module.velocity.y = 0;
		if (module.sprite->getName() == "Player")
		{
			player->SetActState(ACT::IDLE);
		}
		if (module.sprite->getName() == "Enemy")
		{
			enemy->SetActState(ACT::IDLE);
		}
		return false;
	}
	sp.setPosition(sp.getPosition().x + module.velocity.x, sp.getPosition().y + module.velocity.y);
	//module.sprite->runAction(cocos2d::MoveBy::create(0.0f, Vec2(module.velocity.x, module.velocity.y)));
	
	return true;
}
