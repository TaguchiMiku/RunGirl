#include "ItemCreate.h"
#include "item/NormalItem.h"
#include "item/HpItem.h"
#include "obj/Player.h"
#include "Score.h"
#include "debug/_DebugConOut.h"

USING_NS_CC;

ItemCreate * ItemCreate::createItemC()
{
	return ItemCreate::create();
}

ItemCreate::ItemCreate()
{
	listCnt = 0;
}

ItemCreate::~ItemCreate()
{
}

void ItemCreate::AddCreateList(TMXTiledMap * map, cocos2d::Vec2 tile, int num)
{
	if (num == 3)
	{
		//�ʏ�A�C�e�����W
		normalItemList.push_back(Vec2(map->getPosition().x + tile.x * map->getTileSize().width, (map->getMapSize().height - 1 - tile.y) * map->getTileSize().height));
	}
	if (num == 4)
	{
		//HP�񕜃A�C�e�����W
		hpItemList.push_back(Vec2(map->getPosition().x + tile.x * map->getTileSize().width, (map->getMapSize().height - 1 - tile.y) * map->getTileSize().height));
	}
}

void ItemCreate::Push(Layer* layer)
{
	for (auto item1 : normalItemList)
	{
		//�ʏ�A�C�e���ǉ�
		auto nItem = NormalItem::createNItem();
		nItem->setTexture("image/Sprites/item/bonus3.png");
		nItem->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		nItem->setPosition(item1);
		nItem->setName("normalItem");
		nItem->setScale(0.5f, 0.5f);
		//layer->addChild(nItem, 2);
		//nItemSpList.push_back(nItem);
	}
	for (auto item2 : hpItemList)
	{
		//HP�񕜃A�C�e���ǉ�
		auto hpItem = HpItem::createHpItem();
		hpItem->setTexture("image/Sprites/item/n_item.png");
		hpItem->setPosition(item2);
		hpItem->setName("normalItem");
		hpItem->setScale(0.5f, 0.5f);
		layer->addChild(hpItem, 2);
		hpItemSpList.push_back(hpItem);
	}
}

void ItemCreate::Update(float flam, Player* player, Score* score)
{
	plRect = player->getBoundingBox();
	listCnt = 0;
	//�A�C�e���擾
	for (auto item1 : nItemSpList)
	{
		auto nItemRect = item1->getBoundingBox();
		if (plRect.intersectsRect(nItemRect))
		{
			//fxActList.push_back(std::make_pair(item1, lpAnimCtl.RunAnimation(item1, "Fx-glow", 4)));
			//lpSoundMng.OnceSoundPlay("Resources/sound/jump.ckb");
			if (nItemSpList[listCnt] != nullptr)
			{
				player->SetAccelFlag(true);
				nItemSpList.at(listCnt)->SetDeathFlag(true);
				lpAnimCtl.RunAnimation(item1, "Fx-glow", 4);
				score->AddScore(30);
			}
			break;
		}
		listCnt++;
	}
	listCnt = 0;
	for (auto item2 : hpItemSpList)
	{
		auto hpItemRect = item2->getBoundingBox();
		if (plRect.intersectsRect(hpItemRect))
		{
			//fxActList.push_back(std::make_pair(item2, lpAnimCtl.RunAnimation(item2, "Fx-glow", 4)));
			//lpSoundMng.OnceSoundPlay("Resources/sound/jump.ckb");
			if (hpItemSpList[listCnt] != nullptr)
			{
				player->SetAccelFlag(true);
				hpItemSpList.at(listCnt)->SetDeathFlag(true);
				lpAnimCtl.RunAnimation(item2, "Fx-glow", 4);
				score->AddScore(50);
			}
			break;
		}
		listCnt++;
	}
	//listCnt = 0;
	//for (auto fx : fxActList)
	//{
	//	//�G�t�F�N�g�i�A�j���[�V�����j�̍Đ����I�������sprite�Ɣz��̗v�f�������B
	//	if (fx.second->isDone())
	//	{
	//		TRACE("Destroy_Item\n");
	//		fx.first->removeFromParentAndCleanup(true);
	//		fx.second->release();
	//		fxActList.erase(fxActList.begin() + listCnt);
	//	}
	//	listCnt++;
	//}
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
}

void ItemCreate::ClearList()
{
	normalItemList.clear();
	nItemSpList.clear();
	hpItemList.clear();
	hpItemSpList.clear();
	fxActList.clear();
}
