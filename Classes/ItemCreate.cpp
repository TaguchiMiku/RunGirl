#include "ItemCreate.h"
#include "item/NormalItem.h"
#include "item/HpItem.h"
#include "item/FxGlow.h"
#include "obj/Player.h"
#include "MapCreate.h"
#include "Score.h"
#include "sound/SoundMng.h"
//#include "debug/_DebugConOut.h"

USING_NS_CC;

ItemCreate * ItemCreate::createItemC()
{
	return ItemCreate::create();
}

ItemCreate::ItemCreate()
{
	listCnt = 0;
	playerPos = Vec2(0, 0);
}

ItemCreate::~ItemCreate()
{
}

void ItemCreate::AddCreateList(TMXTiledMap * map, cocos2d::Vec2 tile, int num)
{
	if (num == 3)
	{
		//通常アイテム座標
		normalItemList.push_back(Vec2(map->getPosition().x + tile.x * map->getTileSize().width, (map->getMapSize().height - 1 - tile.y) * map->getTileSize().height));
	}
	if (num == 4)
	{
		//HP回復アイテム座標
		hpItemList.push_back(Vec2(map->getPosition().x + tile.x * map->getTileSize().width, (map->getMapSize().height - 1 - tile.y) * map->getTileSize().height));
	}
}

void ItemCreate::Push(Layer* layer)
{
	for (auto item1 : normalItemList)
	{
		//加速アイテム追加
		auto accelItem = NormalItem::createNItem();
		accelItem->setTexture("image/Sprites/item/lightning.png");
		accelItem->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		accelItem->setPosition(item1);
		accelItem->setName("normalItem");
		accelItem->setScale(0.3f, 0.3f);
		layer->addChild(accelItem, 2);
		nItemSpList.push_back(accelItem);

	}
	for (auto item2 : hpItemList)
	{
		//得点UPアイテム追加
		auto hpItem = HpItem::createHpItem();
		auto num = cocos2d::random(1, 3);
		hpItem->setTexture("image/Sprites/item/bonus" + std::to_string(num) + ".png");
		hpItem->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		hpItem->setPosition(item2);
		hpItem->setName("normalItem");
		hpItem->setScale(0.5f, 0.5f);
		layer->addChild(hpItem, 2);
		hpItemSpList.push_back(hpItem);
	}
	this->layer = layer;
}

void ItemCreate::Update(float flam, Player* player, Score* score)
{
	plRect = player->getBoundingBox();
	listCnt = 0;
	//アイテム取得
	for (auto item1 : nItemSpList)
	{
		auto nItemRect = item1->getBoundingBox();
		if (plRect.intersectsRect(nItemRect))
		{
			auto fxGlow = FxGlow::createHpItem();
			fxGlow->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
			fxGlow->setPosition(item1->getPosition());
			fxGlow->setScale(item1->getScale());
			lpAnimCtl.RunAnimation(fxGlow, "Fx-glow", 4, 3);
			layer->addChild(fxGlow, 2);
			fxActSpList.push_back(fxGlow);
			if ((nItemSpList[listCnt] != nullptr) && (!item1->GetDeathFlag()))
			{
				lpSoundMng.OnceSoundPlay("sound/jump2.ckb");
				light++;
				player->SetAccelFlag(true);
				item1->SetDeathFlag(true);
				item1->setScale(0, 0);
				score->AddScore(30);
				score->AddLight(1);
			}
			break;
		}
		if (player->getPosition().x - item1->getPosition().x > 1000)
		{
			item1->SetDeathFlag(true);
		}
		listCnt++;
	}
	listCnt = 0;
	for (auto item2 : hpItemSpList)
	{
		auto hpItemRect = item2->getBoundingBox();
		if (plRect.intersectsRect(hpItemRect))
		{
			auto fxGlow = FxGlow::createHpItem();
			fxGlow->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
			fxGlow->setPosition(item2->getPosition());
			fxGlow->setScale(item2->getScale());
			lpAnimCtl.RunAnimation(fxGlow, "Fx-glow", 4, 3);
			layer->addChild(fxGlow, 2);
			fxActSpList.push_back(fxGlow);
			if ((hpItemSpList[listCnt] != nullptr) && (!item2->GetDeathFlag()))
			{
				lpSoundMng.OnceSoundPlay("sound/jump2.ckb");
				item2->SetDeathFlag(true);
				item2->setScale(0, 0);
				score->AddScore(50);
				score->AddCandy(1);
			}
			break;
		}
		if (player->getPosition().x - item2->getPosition().x > 1000)
		{
			item2->SetDeathFlag(true);
		}
		listCnt++;
	}
	listCnt = 0;
	for (auto fx : fxActSpList)
	{
		//エフェクト（アニメーション）の再生が終わったらspriteと配列の要素を消す。
		if (fx->getNumberOfRunningActionsByTag(3) <= 0)
		{
			fx->SetDeathFlag(true);
		}
		listCnt++;
	}
}

void ItemCreate::DeathCheck()
{
	auto death_nitem = std::remove_if(nItemSpList.begin(), nItemSpList.end(),
		[](NormalItem* nItem) {
		if (nItem->GetDeathFlag())
		{
			nItem->removeFromParentAndCleanup(true);
		}
		return nItem->GetDeathFlag();
	});
	nItemSpList.erase(death_nitem, nItemSpList.end());
	auto death_hp = std::remove_if(hpItemSpList.begin(), hpItemSpList.end(),
		[](HpItem* hpItem) {
		if (hpItem->GetDeathFlag())
		{
			hpItem->removeFromParentAndCleanup(true);
		}
		return hpItem->GetDeathFlag();
	});
	hpItemSpList.erase(death_hp, hpItemSpList.end());

	auto death_fx = std::remove_if(fxActSpList.begin(), fxActSpList.end(),
		[this](FxGlow* fxGlow) {
		if (fxGlow->GetDeathFlag())
		{
			fxGlow->removeFromParentAndCleanup(true);
		}
		return fxGlow->GetDeathFlag();
	});
	fxActSpList.erase(death_fx, fxActSpList.end());
}

void ItemCreate::ClearList()
{
	normalItemList.clear();
	hpItemList.clear();
}
