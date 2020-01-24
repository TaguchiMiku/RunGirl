#pragma once
#include "cocos2d.h"
#include <vector>

class Player;
class Attack;
class Score;
class Enemy;
class EnemyCreate : public cocos2d::Node
{
public:
	EnemyCreate* createEnemyC();
	EnemyCreate();
	~EnemyCreate();

	void AddCreateList(cocos2d::TMXTiledMap * map, cocos2d::Vec2 tile);
	void Push(cocos2d::Layer* layer);
	void Update(float flam, Player* player, Attack* attack, Score* score);
	void DeathCheck();
	void ClearList();
	CREATE_FUNC(EnemyCreate);
private:
	std::vector<cocos2d::Vec2> sponeList;			//敵スポーン座標リスト
	std::vector<Enemy*> sponeSpList;		//敵スプライトリスト
	cocos2d::Rect plRect;
	cocos2d::Sprite* collSpr;
	int listCnt;
	bool onceFlag;
};

