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
	std::vector<cocos2d::Vec2> normalItemList;		//�ʏ�A�C�e�����W���X�g
	std::vector<NormalItem*> nItemSpList;		//�ʏ�A�C�e�����X�g
	std::vector<cocos2d::Vec2> hpItemList;			//HP�񕜃A�C�e�����W���X�g
	std::vector<HpItem*> hpItemSpList;		//HP�񕜃A�C�e�����X�g
	std::vector<FxGlow*> fxActSpList;		//�G�t�F�N�g�̃A�N�V�������X�g
	cocos2d::Rect plRect;
	cocos2d::Vec2 playerPos;
	cocos2d::Layer* layer;
	int listCnt;
};

