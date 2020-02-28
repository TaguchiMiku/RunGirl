#pragma once
#include "cocos2d.h"
#include <vector>

class Player;
class Score;
class SpeedUpItem;
class PointUpItem;
class Item;
class FxGlow;

class ItemGenerate : public cocos2d::Node
{
public:
	ItemGenerate();
	~ItemGenerate();
	ItemGenerate* createItemC();
	void Init();
	void AddCreateList(cocos2d::TMXTiledMap * map, cocos2d::Vec2 tile, int num);
	void CreateItem(cocos2d::Layer* layer);
	void Create(Item* item, std::string fileName, std::string name, cocos2d::Layer * layer, cocos2d::Vec2 position, float scale);
	void Update(float flam, Player* player, Score* score);
	void DeathCheck();
	CREATE_FUNC(ItemGenerate);
private:
	std::vector<cocos2d::Vec2> normalItemList;		//通常アイテム座標リスト
	std::vector<cocos2d::Vec2> hpItemList;			//HP回復アイテム座標リスト
	std::vector<FxGlow*> fxActSpList;		//エフェクトのアクションリスト
	std::vector<Item*> itemList;
	cocos2d::Rect plRect;
	cocos2d::Vec2 playerPos;
	cocos2d::Layer* layer;
	int listCnt;
};

