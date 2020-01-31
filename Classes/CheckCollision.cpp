#include "CheckCollision.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "MapCreate.h"
//#include "debug/_DebugConOut.h"
#include <array>

USING_NS_CC;

bool CheckCollision::operator()(cocos2d::Sprite& sp, actModule& module)
{
	//DirectorからTMXTiledMapの情報を取得
	director = cocos2d::Director::getInstance();
	if (director->getRunningScene()->getName() != "Game")
	{
		return false;
	}
	auto mapMng = (MapCreate*)director->getRunningScene()->getChildByName("BG_BACKGROUND")->getChildByName("mapMng");
	map = mapMng->GetMap();

	//取得したTMXTiledMapの情報内のTMXLayer型のレイヤー情報を取得
	lay = (cocos2d::TMXLayer*)map->getLayer("ground");

	uint32_t tile;
	for (auto col : module.offset)
	{
		col = Vec2((floor(sp.getPosition().x - mapMng->GetMapSize().width * map->getTileSize().width) + col.x + module.velocity.x), floor(sp.getPosition().y + col.y + module.velocity.y));
		//現在の座標をマス目単位になおす
		tileX = col.x / map->getTileSize().width;
		if (tileX > 0)
		{
			//現在のプレイヤーの座標がどのマップか判定する。その際に難マップめかが必要
			tileX %= (int)map->getMapSize().width;
		}
		tileY = (map->getMapSize().height) - (col.y / map->getTileSize().height);
		//画面の範囲外まで移動していたら進まないようにする
		if ((tileX < 0 || tileX >= map->getMapSize().width)
			|| tileY < 0 || tileY >= map->getMapSize().height)
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
		//引数で指定したマス目の情報をtileに入れる
		tile = lay->getTileGIDAt(cocos2d::Vec2(tileX, tileY));
		if (tile)
		{
			properties = map->getPropertiesForGID(tile).asValueMap();
			if (properties.at("col").asInt() == 1)
			{
				//タイルのcolの情報が1であればfalseを返す（当たっている）
				return false;
			}
		}
	}
	return true;
}
