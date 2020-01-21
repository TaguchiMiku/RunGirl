#include "Falling.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "CheckCollision.h"


USING_NS_CC;

//��������
bool Falling::operator()(cocos2d::Sprite & sp, actModule & module)
{
	//�󒆂ɂ������ɗ���������
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

	//�n�ʂƓ��������痎�����Ȃ�
	//�E���̓����蔻��
	module.offset = { 25, -120 };
	if (!CheckCollision()(*module.sprite, module))
	{
		auto director = cocos2d::Director::getInstance();
		auto map = (cocos2d::TMXTiledMap*)director->getRunningScene()->getChildByName("BG_BACKGROUND")->getChildByName("map");
		//�悭�킩��Ȃ�1.6f(�؂�̂�������1.0f���ƃ}�X�ڂ̐^�񒆂Ŏ~�܂�A1.5f�ɂ���Ƃ��傤�ǃ}�X�ڂ̃f�[�^������Ă�̂��m�~�^���ɂȂ�̂�+0.1����1.6f�ł��ꂢ�Ɏ~�܂����B��B)
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
	//�����̓����蔻��
	module.offset = { -25, -120 };
	if (!CheckCollision()(*module.sprite, module))
	{
		auto director = cocos2d::Director::getInstance();
		auto map = (cocos2d::TMXTiledMap*)director->getRunningScene()->getChildByName("BG_BACKGROUND")->getChildByName("map");
		//�悭�킩��Ȃ�1.6f(�؂�̂�������1.0f���ƃ}�X�ڂ̐^�񒆂Ŏ~�܂�A1.5f�ɂ���Ƃ��傤�ǃ}�X�ڂ̃f�[�^������Ă�̂��m�~�^���ɂȂ�̂�+0.1����1.6f�ł��ꂢ�Ɏ~�܂����B��B)
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
