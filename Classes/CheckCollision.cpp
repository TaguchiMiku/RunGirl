#include "CheckCollision.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "MapCreate.h"
//#include "debug/_DebugConOut.h"
#include <array>

USING_NS_CC;

bool CheckCollision::operator()(cocos2d::Sprite& sp, actModule& module)
{
	//Director����TMXTiledMap�̏����擾
	director = cocos2d::Director::getInstance();
	if (director->getRunningScene()->getName() != "Game")
	{
		return false;
	}
	auto mapMng = (MapCreate*)director->getRunningScene()->getChildByName("BG_BACKGROUND")->getChildByName("mapMng");
	map = mapMng->GetMap();
	/*if (map->getMapSize().width >= 165)
	{
		TRACE("mapA\n");
	}
	if (map->getMapSize().width <= 165)
	{
		TRACE("mapB\n");
	}*/
	
	//�擾����TMXTiledMap�̏�����TMXLayer�^�̃��C���[�����擾
	lay = (cocos2d::TMXLayer*)map->getLayer("ground");

	player = static_cast<Player*>(module.sprite);
	std::array<Vec2, 2> colList;
	pos = Vec2((sp.getPosition().x - mapMng->GetMapSize().width * map->getTileSize().width) + module.offset.x, sp.getPosition().y + module.offset.y);
	visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	uint32_t tile;
	if (module.action == ACT::RIGHT)
	{
		colList[0] = Vec2((sp.getPosition().x - mapMng->GetMapSize().width * map->getTileSize().width) + module.offset.x, sp.getPosition().y + module.offset.y);
		colList[1] = Vec2((sp.getPosition().x - mapMng->GetMapSize().width * map->getTileSize().width) + 25, sp.getPosition().y + 20);
		
		for (auto col : colList)
		{
			//��ʂ͈̔͊O�܂ňړ����Ă�����i�܂Ȃ��悤�ɂ���
			if (col.x < 0 || col.x >(map->getMapSize().width * map->getTileSize().width)
				|| col.y < -map->getTileSize().height - 1 || col.y >(map->getMapSize().height * map->getTileSize().height))
			{
				player->SetActState(ACT::DIE);
				return false;
			}
			//���݂̍��W���}�X�ڒP�ʂɂȂ���
			tileX = col.x / map->getTileSize().width;
			tileY = (map->getMapSize().height - 1) - (col.y / map->getTileSize().height);
			//�����Ŏw�肵���}�X�ڂ̏���tile�ɓ����
			tile = lay->getTileGIDAt(cocos2d::Vec2((int)tileX, (int)tileY));
			if (tile)
			{
				properties = map->getPropertiesForGID(tile).asValueMap();
				if (properties.at("col").asInt() == 1)
				{
					//�^�C����col�̏��1(��`����p)�ł����true��Ԃ�
					return false;
				}
			}
		}
	}
	else
	{
		//��ʂ͈̔͊O�܂ňړ����Ă�����i�܂Ȃ��悤�ɂ���
		if (pos.x < 0 || pos.x >(map->getMapSize().width * map->getTileSize().width)
			|| pos.y < -map->getTileSize().height - 1 || pos.y >(map->getMapSize().height * map->getTileSize().height))
		{
			player->SetActState(ACT::DIE);
			return true;
		}
		//���݂̍��W���}�X�ڒP�ʂɂȂ���
		tileX = pos.x / map->getTileSize().width;
		tileY = (map->getMapSize().height - 1) - (pos.y / map->getTileSize().height);
		//�����Ŏw�肵���}�X�ڂ̏���tile�ɓ����
		tile = lay->getTileGIDAt(cocos2d::Vec2((int)tileX, (int)tileY));
		if (tile)
		{
			properties = map->getPropertiesForGID(tile).asValueMap();
			if (properties.at("col").asInt() == 1)
			{
				//�^�C����col�̏��1(��`����p)�ł����true��Ԃ�
				return false;
			}
		}
	}
	return true;
}
