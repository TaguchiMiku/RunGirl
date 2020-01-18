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

	//Releseの際にデータが壊れているっぽい
	//delete background;
	//delete background2;
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
	this->setName("Game");
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//レイヤー作成（bgBackLayer、bgFrontLayer, plLayer）
	auto bgBackLayer = Layer::create();
	bgBackLayer->setName("BG_BACKGROUND");
	this->addChild(bgBackLayer, BG_BACK);

	auto bgFrontLayer = Layer::create();
	bgFrontLayer->setName("BG_BACKGROUND");
	this->addChild(bgFrontLayer, BG_FRONT);

	auto plLayer = Layer::create();
	plLayer->setName("BG_BACKGROUND");
	this->addChild(plLayer, PLAYER);

	//UI用カメラ追加
	auto screenSize = Director::getInstance()->getWinSize();
	auto camera = Camera::createOrthographic(screenSize.width, screenSize.height, -768, 768);
	this->addChild(camera);
	camera->setCameraFlag(CameraFlag::USER1);
	camera->setPosition3D(Vec3(0.0f, 0.0f, 0.0f));
	camera->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));
	camera->setDepth(0.0f);
	//UIレイヤー
	uiLayer = Layer::create();
	this->addChild(uiLayer, UI);
	uiLayer->setName("UI_LAYER");
	//UI追加
	auto hp = Sprite::create("image/Environment/gree_bar.jpg");
	hp->setName("HP");
	hp->setPosition(cocos2d::Vec2(300, 520));
	uiLayer->addChild(hp, 0);

	//背景追加
	background = Sprite::create("image/Environment/back_sky.png");
	background->setName("back1");
	background->setAnchorPoint(cocos2d::Vec2(0, 0));
	bgBackLayer->addChild(background, BG_BACK);

	//map描画
	tilemap = TMXTiledMap::create("image/Environment/test2.tmx");
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
	
	for (auto list : sponeList)
	{
		//Enemy追加
		enemy = Enemy::createEnemy();
		enemy->setPosition(list);
		plLayer->addChild(enemy, PLAYER);
		sponeSpList.push_back(enemy);
	}

	////Player追加
	player = Player::createPlayer();
	plLayer->addChild(player, PLAYER);

	manager = efk::EffectManager::create(Director::getInstance()->getVisibleSize());
	lpEffectMng.Init(*plLayer, manager);
	effect = lpEffectMng.Play("drill", Vec2(player->getPosition().x + 20, player->getPosition().y - 110), 20, 1.0f, true);
	effect->setRotation3D(Vec3(0, -90.0f, 0));
	//sound = lpSoundMng.SoundLoopPlay("Resources/sound/bgm1.ckb");

	//lpAnimCtl.AddAnimation("Fx", "glow", 0.05f);
	//ef = lpEffectMng.Play("Laser01", Vec2(player->getPosition().x, player->getPosition().y - 110), 5, 1.0f, true);

	scaleX = 1;
	score = Score::createScore();
	this->addChild(score, 0);

	//スコア表示初期化
	/*auto scoreLabel = Label::createWithTTF("Score", "../Resources/fonts/Molot.otf", 24);
	scoreLabel->setPosition(Vec2(origin.x + visibleSize.width - visibleSize.width / 4, label->getContentSize().height));
	uiLayer->addChild(scoreLabel, LABEL);

	auto scoreNum = score->DrawScore();
	scoreNum->setPosition(Vec2(origin.x + visibleSize.width - 100, label->getContentSize().height));
	scoreNum->setName("scoreNum");
	uiLayer->addChild(scoreNum, LABEL);*/

	onceFlag = true;
	//UIレイヤーにUI用カメラを適用
	uiLayer->setCameraMask(static_cast<int>(CameraFlag::USER1));

	//this->scheduleUpdate();
    return true;
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void GameScene::update(float delta)
{
	//lpSoundMng.Update();
	manager->update();
	/*auto scoreNum = uiLayer->getChildByName("scoreNum");
	static_cast<Label*>(scoreNum)->setString(std::to_string(score->GetScore()));*/
	plRect = player->getBoundingBox();

	if (player != nullptr && enemy != nullptr)
	{
		onceFlag = true;
		//for (auto ene : sponeSpList)
		//{
		//	eneRect = ene->getBoundingBox();
		//	if (plRect.intersectsRect(eneRect))
		//	{
		//		if (ene == collSpr)
		//		{
		//			//敵と当たり続けていたらfalseにしてHPの減らしをなくす
		//			onceFlag = false;
		//		}
		//		if (onceFlag && player->GetActState() != ACT::ATTACK)
		//		{
		//			collSpr = ene;
		//			scaleX -= 0.2f;
		//			hpBar = uiLayer->getChildByName("HP");
		//			before = hpBar->getBoundingBox().size.width;
		//			hpBar->setScale(scaleX, 1);
		//			after = hpBar->getBoundingBox().size.width;
		//			hpBar->setPosition(hpBar->getPosition().x - (before - after) / 2, hpBar->getPosition().y);
		//			//lpSoundMng.OnceSoundPlay("Resources/sound/die.ckb");
		//			onceFlag = false;
		//			//score->AddScore(-10);
		//		}
		//		else
		//		{
		//			//score->AddScore(100);
		//		}
		//		player->SetActState(ACT::DIE);
		//		break;
		//	}
		//}
	}

	if (player != nullptr)
	{
		/*if(player->GetAccelFlag())
		{
			effect->setScale(20);
		}
		else
		{
			effect->setScale(0);
		}*/
		listCnt = 0;
		//アイテム取得
	//	for (auto item1 : nItemSpList)
	//	{
	//		nItemRect = item1->getBoundingBox();
	//		if (plRect.intersectsRect(nItemRect))
	//		{		
	//			//fxActList.push_back(std::make_pair(item1, lpAnimCtl.RunAnimation(item1, "Fx-glow", 4)));
	//			//lpSoundMng.OnceSoundPlay("Resources/sound/jump.ckb");
	//			if (nItemSpList[listCnt] != nullptr)
	//			{
	//				player->SetAccelFlag(true);
	//				nItemSpList.erase(nItemSpList.begin() + listCnt);
	//			}
	//			//score->AddScore(30);
	//			break;
	//		}
	//		listCnt++;
	//	}
	//	listCnt = 0;
	//	for (auto item2 : hpItemSpList)
	//	{
	//		hpItemRect = item2->getBoundingBox();
	//		if (plRect.intersectsRect(hpItemRect))
	//		{
	//			//fxActList.push_back(std::make_pair(item2, lpAnimCtl.RunAnimation(item2, "Fx-glow", 4)));
	//			//lpSoundMng.OnceSoundPlay("Resources/sound/jump.ckb");
	//			if (hpItemSpList[listCnt] != nullptr)
	//			{
	//				player->SetAccelFlag(true);
	//				hpItemSpList.erase(hpItemSpList.begin() + listCnt);
	//				//score->AddScore(50);
	//			}
	//			break;
	//		}
	//		listCnt++;
	//	}
	//	listCnt = 0;
	//	for (auto fx : fxActList)
	//	{
	//		//エフェクト（アニメーション）の再生が終わったらspriteと配列の要素を消す。
	//		/*if (fx.second->isDone())
	//		{
	//			fx.first->removeFromParentAndCleanup(true);
	//			fx.second->release();
	//			fxActList.erase(fxActList.begin() + listCnt);
	//		}
	//		listCnt++;*/
	//	}
	}
}

void GameScene::visitor(cocos2d::Renderer * renderer, const cocos2d::Mat4 & parentTransform, uint32_t parentFlags)
{
	manager->begin(renderer, _globalZOrder);
	Scene::visit(renderer, parentTransform, parentFlags);
	manager->end(renderer, _globalZOrder);
}

