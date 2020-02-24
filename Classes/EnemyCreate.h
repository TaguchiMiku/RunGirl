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
	EnemyCreate();
	~EnemyCreate();
	EnemyCreate* createEnemyC();

	void AddCreateList(cocos2d::TMXTiledMap * map, cocos2d::Vec2 tile);
	void Push(cocos2d::Layer* layer);
	void Update(float flam, Player* player, Score* score);
	void DeathCheck();
	void ClearList();
	std::vector<Enemy*> GetEnSpriteList();
	CREATE_FUNC(EnemyCreate);
private:
	std::vector<cocos2d::Vec2> sponeList;//�G�X�|�[�����W���X�g
	std::vector<Enemy*> enSpList;		 //�G�X�v���C�g���X�g
	cocos2d::Rect plRect;
};

