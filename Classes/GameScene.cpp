/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GameScene.h"
#include "obj/Player.h"
#include "obj/Enemy.h"
#include "item/HpItem.h"
#include "item/NormalItem.h"
#include "Score.h"
#include "ui/BackScroll.h"
#include "ui/Attack.h"
//#include "sound/SoundMng.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "debug/_DebugConOut.h"
//#include "../debug/_DebugDispOut.h"//
#endif

#pragma execution_charactor_set("utf-8");

USING_NS_CC;

GameScene::~GameScene()
{
	//sound->stop();
	//sound->destroy();
}

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
#if (_DEBUG &&CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	_DebugConOut::GetInstance();
#else
#endif
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
	this->setName("Game");

	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//レイヤー作成（bgBackLayer、bgFrontLayer, plLayer）
	auto bgBackLayer = Layer::create();
	bgBackLayer->setName("BG_BACKGROUND");
	this->addChild(bgBackLayer, 0);

	auto bgFrontLayer = Layer::create();
	bgFrontLayer->setName("BG_BACKGROUND");
	this->addChild(bgFrontLayer, 2);

	auto plLayer = Layer::create();
	plLayer->setName("BG_BACKGROUND");
	this->addChild(plLayer, 1);

	//UI用カメラ追加
	auto screenSize = Director::getInstance()->getWinSize();
	auto camera = Camera::createOrthographic(screenSize.width, screenSize.height, -768, 768);
	this->addChild(camera);
	camera->setCameraFlag(CameraFlag::USER1);
	camera->setPosition3D(Vec3(0.0f, 0.0f, 0.0f));
	camera->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));
	camera->setDepth(0.0f);
	//UIレイヤー
	auto uiLayer = Layer::create();
	this->addChild(uiLayer, UI);
	uiLayer->setName("UI_LAYER");
	//UI追加
	auto hp = Sprite::create("image/Environment/gree_bar.jpg");
	hp->setName("HP");
	hp->setPosition(cocos2d::Vec2(300, 520));
	uiLayer->addChild(hp, 0);

	//スコア表示初期化
	score = Score::createScore();
	score->setPosition(Vec2(origin.x + visibleSize.width - 200, 40));
	score->ResetScore();
	this->addChild(score, 0);
	score->Init(uiLayer);
	score->DrawScore();

	//UIレイヤーにUI用カメラを適用
	uiLayer->setCameraMask(static_cast<int>(CameraFlag::USER1));

	//背景追加
	backSrl = BackScroll::create();
	if (backSrl != nullptr)
	{
		backSrl->Init(Vec2(0, 0), Vec2(1.0f, 1.0f), bgBackLayer);
	}

	//map描画
	auto tilemap = TMXTiledMap::create("image/Environment/test2.tmx");
	tilemap->setName("map");
	tilemap->setPosition(0, 0);
	bgBackLayer->addChild(tilemap, BG_BACK);

	//map内のタイル全検索
	for (int y = 0; y < tilemap->getMapSize().height; y++)
	{
		for (int x = 0; x < tilemap->getMapSize().width; x++)
		{
			auto lay = tilemap->getLayer("ground");
			auto tile = lay->getTileGIDAt(cocos2d::Vec2(x, y));
			if (tile)
			{
				auto properties = tilemap->getPropertiesForGID(tile).asValueMap();
				if (properties.at("col").asInt() == 2)
				{
					//敵スポーン座標
					sponeList.push_back(Vec2(x * tilemap->getTileSize().width, (tilemap->getMapSize().height - 1 - y) * tilemap->getTileSize().height + 100));
				}
				else if (properties.at("col").asInt() == 3)
				{
					//通常アイテム座標
					normalItemList.push_back(Vec2(x * tilemap->getTileSize().width, (tilemap->getMapSize().height - 1 - y) * tilemap->getTileSize().height));
				}
				else if (properties.at("col").asInt() == 4)
				{
					//HP回復アイテム座標
					hpItemList.push_back(Vec2(x * tilemap->getTileSize().width, (tilemap->getMapSize().height - 1 - y) * tilemap->getTileSize().height));
				}
			}
		}
	}

	for (auto item1 : normalItemList)
	{
		//通常アイテム追加
		auto nItem = NormalItem::createNItem("image/Sprites/item/coin.png");
		nItem->setPosition(item1);
		nItem->setName("normalItem");
		nItem->setScale(0.5f, 0.5f);
		plLayer->addChild(nItem, 2);
		nItemSpList.push_back(nItem);
	}
	for (auto item2 : hpItemList)
	{
		//HP回復アイテム追加
		auto hpItem = HpItem::createHpItem("image/Sprites/item/n_item.png");
		hpItem->setPosition(item2);
		hpItem->setName("normalItem");
		hpItem->setScale(0.5f, 0.5f);
		plLayer->addChild(hpItem, 2);
		hpItemSpList.push_back(hpItem);
	}
	
	//敵の追加
	for (auto list : sponeList)
	{
		//Enemy追加
		enemy = Enemy::createEnemy();
		enemy->setPosition(list);
		plLayer->addChild(enemy, PLAYER);
		sponeSpList.push_back(enemy);
	}

	//Player追加
	player = Player::createPlayer();
	plLayer->addChild(player, PLAYER);

	attack = Attack::createAttack();
	if (attack != nullptr)
	{
		attack->Init(Vec2(player->getPosition().x + 10, player->getPosition().y), Vec2(1.0f, 1.0f), plLayer);
	}

	manager = efk::EffectManager::create(Director::getInstance()->getVisibleSize());
	lpEffectMng.Init(*plLayer, manager);
	effect = lpEffectMng.Play("drill", Vec2(player->getPosition().x + 20, player->getPosition().y - 110), 20, 1.0f, true);
	lpEffectMng.Play("starTap", Vec2(player->getPosition().x + 20, player->getPosition().y - 110), 20, 1.0f, false);

	if (effect != nullptr)
	{
		effect->setRotation3D(Vec3(0, -90.0f, 0));
	}
	//sound = lpSoundMng.SoundLoopPlay("Resources/sound/bgm1.ckb");

	lpAnimCtl.AddAnimation("Fx", "glow", 0.05f);

	scaleX = 1;
	onceFlag = true;

	this->scheduleUpdate();
    return true;
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void GameScene::update(float delta)
{
	//lpSoundMng.Update();
	if (manager != nullptr)
	{
		manager->update();
	}
	auto uiLayer = getChildByName("UI_LAYER");
	score->DrawScore();
	plRect = player->getBoundingBox();
	listCnt = 0;
	if (player != nullptr && enemy != nullptr)
	{
		onceFlag = true;
		for (auto ene : sponeSpList)
		{
			eneRect = ene->getBoundingBox();
			atkRect = attack->getBoundingBox();
			if (plRect.intersectsRect(eneRect))
			{
				if(player->GetAttackFlag())
				{
					//攻撃時に敵に当たったら消す
					ene->removeFromParentAndCleanup(true);
					sponeSpList.erase(sponeSpList.begin() + listCnt);
					score->AddScore(100);
					attack->setPosition(Vec2(player->getPosition().x + 50, player->getPosition().y));
					lpAnimCtl.RunAnimation(attack, "Fx-impact", 1);
					player->SetAttackFlag(false);
					break;
				}
				if (ene == collSpr)
				{
					//敵と当たり続けていたらfalseにしてHPの減らしをなくす
					onceFlag = false;
				}
				if (onceFlag && player->GetActState() != ACT::ATTACK)
				{
					collSpr = ene;
					scaleX -= 0.2f;
					hpBar = uiLayer->getChildByName("HP");
					before = hpBar->getBoundingBox().size.width;
					hpBar->setScale(scaleX, 1);
					after = hpBar->getBoundingBox().size.width;
					hpBar->setPosition(hpBar->getPosition().x - (before - after) / 2, hpBar->getPosition().y);
					//lpSoundMng.OnceSoundPlay("Resources/sound/die.ckb");
					onceFlag = false;
					score->AddScore(-10);
					player->SetActState(ACT::DIE);
				}
				break;
			}			
			listCnt++;
		}
	}

	if (player != nullptr)
	{
		if (effect != nullptr)
		{
			if (player->GetAccelFlag())
			{
				effect->setScale(20);
			}
			else
			{
				effect->setScale(0);
			}
		}
		listCnt = 0;
		//アイテム取得
		for (auto item1 : nItemSpList)
		{
			nItemRect = item1->getBoundingBox();
			if (plRect.intersectsRect(nItemRect))
			{		
				fxActList.push_back(std::make_pair(item1, lpAnimCtl.RunAnimation(item1, "Fx-glow", 4)));
				//lpSoundMng.OnceSoundPlay("Resources/sound/jump.ckb");
				if (nItemSpList[listCnt] != nullptr)
				{
					player->SetAccelFlag(true);
					nItemSpList.erase(nItemSpList.begin() + listCnt);
					score->AddScore(30);
				}
				break;
			}
			listCnt++;
		}
		listCnt = 0;
		for (auto item2 : hpItemSpList)
		{
			hpItemRect = item2->getBoundingBox();
			if (plRect.intersectsRect(hpItemRect))
			{
				fxActList.push_back(std::make_pair(item2, lpAnimCtl.RunAnimation(item2, "Fx-glow", 4)));
				//lpSoundMng.OnceSoundPlay("Resources/sound/jump.ckb");
				if (hpItemSpList[listCnt] != nullptr)
				{
					player->SetAccelFlag(true);
					hpItemSpList.erase(hpItemSpList.begin() + listCnt);
					score->AddScore(50);
				}
				break;
			}
			listCnt++;
		}
		listCnt = 0;
		for (auto fx : fxActList)
		{
			//エフェクト（アニメーション）の再生が終わったらspriteと配列の要素を消す。
			if (fx.second->isDone())
			{
				fx.first->removeFromParentAndCleanup(true);
				fx.second->release();
				fxActList.erase(fxActList.begin() + listCnt);
			}
			listCnt++;
		}
	}
}

void GameScene::visitor(cocos2d::Renderer * renderer, const cocos2d::Mat4 & parentTransform, uint32_t parentFlags)
{
	manager->begin(renderer, _globalZOrder);
	Scene::visit(renderer, parentTransform, parentFlags);
	manager->end(renderer, _globalZOrder);
}

