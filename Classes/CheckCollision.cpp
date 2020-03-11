#include "CheckCollision.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "MapCreate.h"
//#include "debug/_DebugConOut.h"
#include <array>
#include <cmath>

USING_NS_CC;

// �N���X�̖��O�ς��Ȃ��Ƃ����Ȃ�������NoHit//////////////////////////////

bool CheckCollision::operator()(actModule& module)
{
	// Director����TMXTiledMap�̏����擾
	director = cocos2d::Director::getInstance();
	if (director->getRunningScene()->getName() != "Game")
	{
		return false;
	}

	auto mapMng = (MapCreate*)director->getRunningScene()->getChildByName("BG_BACKGROUND")->getChildByName("mapMng");
	if (mapMng == nullptr)
	{
		return false;
	}
	map = mapMng->GetMap();

	// �擾����TMXTiledMap�̏�����TMXLayer�^�̃��C���[�����擾
	auto player = (Player*)director->getRunningScene()->getChildByName("plLayer")->getChildByName("Player");
	if (player->GetBigModeFlag())
	{
		lay = (cocos2d::TMXLayer*)map->getLayer("special");
	}
	else
	{
		lay = (cocos2d::TMXLayer*)map->getLayer("ground");
	}

	uint32_t tile;
	auto mapSize = map->getMapSize();
	auto tileSize = map->getTileSize();
	for (auto col : module.offset)
	{
		col = Vec2(floor(module.sprite->getPosition().x - mapMng->GetMapSize().width * map->getTileSize().width) + col.x + module.velocity.x,
				   floor(module.sprite->getPosition().y + col.y + module.velocity.y));

		// ���W���}�X�ڒP�ʂɂȂ���
		float tileX = col.x / tileSize.width;
		if (tileX > 0.0f)
		{
			// ���W�����}�b�v�ڂ����肷��
			tileX = fmod(tileX, mapSize.width);
		}
		float tileY = mapSize.height - (col.y / tileSize.height);

		// �����_�ȉ���؂�̂Ă�
		tileX = floor(tileX);
		tileY = floor(tileY);

		// ��ʂ͈̔͊O�܂ňړ����Ă�����i�܂Ȃ��悤�ɂ���
		if ((tileX < 0.0f || tileX >= map->getMapSize().width)
		 || (tileY < 0.0f || tileY >= map->getMapSize().height))
		{
			if (mapMng->GetMapSetFlag() && module.action != ACT::FALL)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		//�����Ŏw�肵���}�X�ڂ̏���tile�ɓ����
		tile = lay->getTileGIDAt(Vec2(tileX, tileY));

		if (tile)
		{
			properties = map->getPropertiesForGID(tile).asValueMap();
			if (properties.at("col").asInt() == 1)
			{
				//�^�C����col�̏��1�ł����false��Ԃ��i�������Ă���j
				return false;
			}
		}

	}
	return true;
}
