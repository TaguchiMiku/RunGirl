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
#include "ui/CountDown.h"
#include "ui/TimerMng.h"
#include "MapCreate.h"
#include "EnemyCreate.h"
#include "ItemCreate.h"
//#include "sound/SoundMng.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "debug/_DebugConOut.h"
#endif
#define COUNT_DOWN_SECOND 3		// ゲーム開始までのカウントダウン(秒)

#pragma execution_charactor_set("utf-8");

USING_NS_CC;

GameScene::~GameScene()
{
	//sound->stop();
	//sound->destroy();
	if (_running)
	{
		onExit();
	}
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
	bgFrontLayer->setName("BG_FRONTGROUND");
	this->addChild(bgFrontLayer, 2);

	auto plLayer = Layer::create();
	plLayer->setName("plLayer");
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
	hp->setPosition(cocos2d::Vec2(260, 30));
	uiLayer->addChild(hp, 0);

	//スコア表示初期化
	score = Score::createScore();
	score->setPosition(Vec2(origin.x + visibleSize.width - 200, 40));
	score->ResetScore();
	score->setName("Score");
	this->addChild(score, 0);
	score->Init(uiLayer);
	score->DrawScore();

	timer = TimerMng::createTimer();
	timer->Init(uiLayer);

	cntDwn = CountDown::createCntDwn();
	cntDwn->Init(uiLayer);

	//UIレイヤーにUI用カメラを適用
	uiLayer->setCameraMask(static_cast<int>(CameraFlag::USER1));

	//Player追加
	player = Player::create();
	plLayer->addChild(player, PLAYER);

	map = MapCreate::create();
	map->Init(bgBackLayer);
	map->setName("mapMng");
	bgBackLayer->addChild(map, BG_BACK);
	auto tilemap = map->GetMap();
	map->ReCreate(tilemap, plLayer);

	auto a = Director::getInstance()->getRunningScene();

	//背景追加
	backSrl = BackScroll::create();
	if (backSrl != nullptr)
	{
		backSrl->Init(Vec2(0, 0), Vec2(1.0f, 1.0f), bgBackLayer);
	}

	attack = Attack::createAttack();
	if (attack != nullptr)
	{
		attack->Init(Vec2(player->getPosition().x + 10, player->getPosition().y), Vec2(1.0f, 1.0f), plLayer);
	}
	
	effect = lpEffectMng.Play("drill", Vec2(player->getPosition().x + 20, player->getPosition().y - 110), 20, 1.0f, true);
	plLayer->addChild(effect, 0);
	/*auto tapEfk = lpEffectMng.Play("starTap", Vec2(player->getPosition().x + 20, player->getPosition().y - 110), 20, 1.0f, false);
	plLayer->addChild(tapEfk, 1);*/
	if (effect != nullptr)
	{
		effect->setRotation3D(Vec3(0, -90.0f, 0));
	}
	//sound = lpSoundMng.SoundLoopPlay("Resources/sound/bgm1.ckb");

	lpAnimCtl.AddAnimation("Fx", "glow", 0.05f);

	scaleX = 1;
	onceFlag = true;
	timeUpFlag = false;
	gameFlag = false;
	time = 0;

	this->scheduleUpdate();
    return true;
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void GameScene::update(float delta)
{
	if (!gameFlag)
	{
		time += delta;
		if (time >= COUNT_DOWN_SECOND + 1)
		{
			time = 0;
			gameFlag = true;
		}
		return;
	}
	//lpSoundMng.Update();
	if (lpEffectMng.GetEffectManager() != nullptr)
	{
		lpEffectMng.GetEffectManager()->update();
	}
	if (player == nullptr)
	{
		return;
	}
	player->Update(delta);
	if (backSrl != nullptr)
	{
		backSrl->ScrBackSet(player);
	}
	if (score != nullptr && timer != nullptr)
	{
		// TimerとScoreの更新
		score->DrawScore();
		timer->DrawTimer();
		// 制限時間が0になったら2秒後ResultSceneへ遷移する
		if (timer->GetTimerCnt() <= 0 && onceFlag)
		{
			onceFlag = false;
			player->SetTimeUpFlag(true);
			//lpSoundMng.OnceSoundPlay("Resources/sound/jump.ckb");
			this->scheduleOnce(schedule_selector(GameScene::NextScene), 2.0f);
		}
	}
	if (attack != nullptr && score != nullptr)
	{
		enemyCt = map->GetEnemyCt();
		itemCt = map->GetItemCt();
		// プレイヤーとの判定
		enemyCt->Update(delta, player, score);
		itemCt->Update(delta, player, score);
		// 走るエフェクトのON・OFF
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
	}
}

void GameScene::NextScene(float millsecond)
{
	auto scene = ResultScene::createScene();
	auto director = cocos2d::Director::getInstance();
	director->replaceScene(scene);
}

void GameScene::visitor(cocos2d::Renderer * renderer, const cocos2d::Mat4 & parentTransform, uint32_t parentFlags)
{
	lpEffectMng.GetEffectManager()->begin(renderer, _globalZOrder);
	Scene::visit(renderer, parentTransform, parentFlags);
	lpEffectMng.GetEffectManager()->end(renderer, _globalZOrder);
}

