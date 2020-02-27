#include "CheckCollision.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "MapCreate.h"
//#include "debug/_DebugConOut.h"
#include <array>

USING_NS_CC;

bool CheckCollision::operator()(actModule& module)
{
	//Director����TMXTiledMap�̏����擾
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

	//�擾����TMXTiledMap�̏�����TMXLayer�^�̃��C���[�����擾
	lay = (cocos2d::TMXLayer*)map->getLayer("ground");

	uint32_t tile;
	for (auto col : module.offset)
	{
		col = Vec2((floor(module.sprite->getPosition().x - mapMng->GetMapSize().width * map->getTileSize().width) + col.x + module.velocity.x), floor(module.sprite->getPosition().y + col.y + module.velocity.y));
		// ���W���}�X�ڒP�ʂɂȂ���
		tileX = static_cast<int>(col.x / map->getTileSize().width);
		if (tileX > 0)
		{
			// ���W�����}�b�v�ڂ����肷��
			tileX %= (int)map->getMapSize().width;
		}
		tileY = (int)(map->getMapSize().height) - (col.y / map->getTileSize().height);

		//��ʂ͈̔͊O�܂ňړ����Ă�����i�܂Ȃ��悤�ɂ���
		if ((tileX < 0 || tileX >= (int)(map->getMapSize().width))
			|| tileY < 0 || tileY >= (int)(map->getMapSize().height))
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
		tile = lay->getTileGIDAt(cocos2d::Vec2((float)tileX, (float)tileY));

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
