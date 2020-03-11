#include "CheckCollision.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "MapCreate.h"
//#include "debug/_DebugConOut.h"
#include <array>
#include <cmath>

USING_NS_CC;

// クラスの名前変えないといけないっすよNoHit//////////////////////////////

bool CheckCollision::operator()(actModule& module)
{
	// DirectorからTMXTiledMapの情報を取得
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

	// 取得したTMXTiledMapの情報内のTMXLayer型のレイヤー情報を取得
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

		// 座標をマス目単位になおす
		float tileX = col.x / tileSize.width;
		if (tileX > 0.0f)
		{
			// 座標が何マップ目か判定する
			tileX = fmod(tileX, mapSize.width);
		}
		float tileY = mapSize.height - (col.y / tileSize.height);

		// 小数点以下を切り捨てる
		tileX = floor(tileX);
		tileY = floor(tileY);

		// 画面の範囲外まで移動していたら進まないようにする
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

		//引数で指定したマス目の情報をtileに入れる
		tile = lay->getTileGIDAt(Vec2(tileX, tileY));

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
