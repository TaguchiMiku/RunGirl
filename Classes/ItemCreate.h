#pragma once
#include "cocos2d.h"
#include <vector>

class Player;
class Score;
class NormalItem;
class HpItem;
class FxGlow;
class ItemCreate : public cocos2d::Node
{
public:
	ItemCreate* createItemC();
	ItemCreate();
	~ItemCreate();

	void AddCreateList(cocos2d::TMXTiledMap * map, cocos2d::Vec2 tile, int num);
	void Push(cocos2d::Layer* layer);
	void Update(float flam, Player* player, Score* score);
	void DeathCheck();
	void ClearList();
	CREATE_FUNC(ItemCreate);
private:
	std::vector<cocos2d::Vec2> normalItemList;		//通常アイテム座標リスト
	std::vector<NormalItem*> nItemSpList;		//通常アイテムリスト
	std::vector<cocos2d::Vec2> hpItemList;			//HP回復アイテム座標リスト
	std::vector<HpItem*> hpItemSpList;		//HP回復アイテムリスト
	std::vector<FxGlow*> fxActSpList;		//エフェクトのアクションリスト
	cocos2d::Rect plRect;
	cocos2d::Vec2 playerPos;
	cocos2d::Layer* layer;
	int listCnt;
};

