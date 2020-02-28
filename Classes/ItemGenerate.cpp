#include "ItemGenerate.h"
#include "item/SpeedUpItem.h"
#include "item/PointUpItem.h"
#include "item/FxGlow.h"
#include "obj/Player.h"
#include "MapCreate.h"
#include "Score.h"
#include "sound/SoundMng.h"

USING_NS_CC;

ItemGenerate::ItemGenerate()
{
	Init();
}

ItemGenerate::~ItemGenerate()
{
}

ItemGenerate * ItemGenerate::createItemC()
{
	return ItemGenerate::create();
}

void ItemGenerate::Init()
{
	listCnt = 0;
	playerPos = Vec2(0.0f, 0.0f);
}

void ItemGenerate::AddCreateList(TMXTiledMap * map, cocos2d::Vec2 tile, int num)
{
	if (num == 3)
	{
		//通常アイテム座標
		normalItemList.push_back(
			Vec2(map->getPosition().x + tile.x * map->getTileSize().width,
				 map->getTileSize().height * (map->getMapSize().height - 1.0f - tile.y))
		);
	}
	if (num == 4)
	{
		//HP回復アイテム座標
		hpItemList.push_back(
			Vec2(map->getPosition().x + tile.x * map->getTileSize().width,
				 map->getTileSize().height * (map->getMapSize().height - 1.0f - tile.y))
		);
	}
}

void ItemGenerate::CreateItem(Layer* layer)
{
	for (auto item1 : normalItemList)
	{
		//加速アイテム追加
		Create(SpeedUpItem::createNItem(), "image/Sprites/item/lightning.png", "SpeedUpItem", layer, item1, 0.3f);
	}
	for (auto item2 : hpItemList)
	{
		//得点UPアイテム追加
		auto num = cocos2d::random(1, 3);
		Create(PointUpItem::createHpItem(), "image/Sprites/item/bonus" + std::to_string(num) + ".png", "PointUpItem", layer, item2, 0.5f);
	}
	this->layer = layer;
}

void ItemGenerate::Create(Item* item, std::string fileName, std::string name, Layer * layer, Vec2 position, float scale)
{
	item->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	item->setPosition(position);
	item->setScale(scale);
	if (name == "SpeedUpItem" || name == "PointUpItem")
	{
		item->setTexture(fileName);
		item->setName(name);
	}
	else
	{
		item->setName(name);
		lpAnimCtl.RunAnimation(item, "Fx-glow", 4, 3);
	}
	layer->addChild(item, 2);
	itemList.push_back(item);
}

void ItemGenerate::Update(float flam, Player* player, Score* score)
{
	plRect = player->getBoundingBox();
	listCnt = 0;
	//アイテム取得
	for (auto item : itemList)
	{
		auto itemRect = item->getBoundingBox();
		if (plRect.intersectsRect(itemRect))
		{	
			if (item->getName() == "FX")
			{
				if (item->getNumberOfRunningActionsByTag(3) <= 0)
				{
					item->SetDeathFlag(true);
				}
			}
			else if ((itemList[listCnt] != nullptr) && (!item->GetDeathFlag()))
			{
				Create(FxGlow::createHpItem(), "", "FX", layer, item->getPosition(), item->getScale());
				lpSoundMng.OnceSoundPlay("sound/jump2.ckb");
				item->SetDeathFlag(true);
				item->setScale(0.0f, 0.0f);
				if (item->getName() == "SpeedUpItem")
				{
					player->SetAccelFlag(true);
					score->AddScore(30);
					score->AddLight(1);
				}			
				if (item->getName() == "PointUpItem")
				{
					score->AddScore(100);
					score->AddCandy(1);
				}
			}
			break;
		}
		if (player->getPosition().x - item->getPosition().x > 1000.0f)
		{
			item->SetDeathFlag(true);
		}
		listCnt++;
	}
	if (itemList.size() > 0 && fxActSpList.size() > 0)
	{
		DeathCheck();
	}
}

void ItemGenerate::DeathCheck()
{
	auto death_item = std::remove_if(itemList.begin(), itemList.end(),
		[this](Item* item) {
		if (item->GetDeathFlag())
		{
			item->removeFromParentAndCleanup(true);
			return true;
		}
		return false;
		}
	);
	itemList.erase(death_item, itemList.end());
}

