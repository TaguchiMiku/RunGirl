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
#include "item/PointUpItem.h"
#include "item/SpeedUpItem.h"
#include "Score.h"
#include "ui/BackScroll.h"
#include "ui/Attack.h"
#include "ui/CountDown.h"
#include "ui/TimerMng.h"
#include "MapCreate.h"
#include "EnemyCreate.h"
#include "ItemGenerate.h"
#include "sound/SoundMng.h"
#include "ResultScene.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "debug/_DebugConOut.h"
#endif
#define COUNT_DOWN_SECOND 3.0f		// ゲーム開始までのカウントダウン(秒)

#pragma execution_charactor_set("utf-8");

USING_NS_CC;

GameScene::~GameScene()
{
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
#if (_DEBUG && CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	_DebugConOut::GetInstance();
#endif
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
	this->addChild(bgBackLayer, 0);

	auto bgFrontLayer = Layer::create();
	bgFrontLayer->setName("BG_FRONTGROUND");
	this->addChild(bgFrontLayer, 2);

	auto plLayer = Layer::create();
	plLayer->setName("plLayer");
	this->addChild(plLayer, 1);

	//UI用カメラ追加
	auto screenSize = Director::getInstance()->getWinSize();
	auto camera = Camera::createOrthographic(screenSize.width, screenSize.height, -768.0f, 768.0f);
	this->addChild(camera);
	camera->setCameraFlag(CameraFlag::USER1);
	camera->setPosition3D(Vec3(0.0f, 0.0f, 0.0f));
	camera->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));
	camera->setDepth(0.0f);

	//UIレイヤー
	auto uiLayer = Layer::create();
	uiLayer->setName("UI_LAYER");
	this->addChild(uiLayer, UI);

	//スコア表示初期化
	score = Score::createScore();
	score->setPosition(Vec2(origin.x + visibleSize.width - 200.0f, 40.0f));
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

	//背景追加
	auto BackGroundSet = [this](std::string fileName, Vec2 position, Vec2 scale, Layer * layer, float speed)
	{
		auto bg = BackScroll::create();
		if (bg != nullptr)
		{
			bg->Init(fileName, position, scale, layer, speed);
			backSrl.emplace_back(bg);
		}
	};
	BackGroundSet("Clouds_4", Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f), bgBackLayer, 0.05f);
	BackGroundSet("Clouds_3", Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f), bgBackLayer, 0.1f);
	BackGroundSet("Clouds_2", Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f), bgBackLayer, 0.2f);
	BackGroundSet("Clouds_1", Vec2(0.0f, 100.0f), Vec2(1.0f, 1.0f), bgBackLayer, 0.5f);

	attack = Attack::createAttack();
	if (attack != nullptr)
	{
		attack->Init(Vec2(player->getPosition().x + 10.0f, player->getPosition().y), Vec2(1.0f, 1.0f), plLayer);
	}
	
	/*auto tapEfk = lpEffectMng.Play("starTap", Vec2(player->getPosition().x + 20, player->getPosition().y - 110), 20, 1.0f, false);
	plLayer->addChild(tapEfk, 1);*/
	lpAnimCtl.AddAnimation("Fx", "glow", 0.05f);

	onceFlag = true;
	timeUpFlag = false;
	gameFlag = false;
	time = 0.0f;

	this->setName("Game");
	this->scheduleUpdate();
    return true;
}

void GameScene::update(float delta)
{
	if (!gameFlag)
	{
		time += delta;
		if (time >= COUNT_DOWN_SECOND + 1.0f)
		{
			time = 0.0f;
			gameFlag = true;
		}
		return;
	}

	lpSoundMng.Update();
	if (lpEffectMng.GetEffectManager() != nullptr)
	{
		lpEffectMng.GetEffectManager()->update();
	}

	if (player == nullptr)
	{
		return;
	}
	player->Update(delta);

	for (auto bg : backSrl)
	{
		if (bg != nullptr)
		{
			bg->ScrBackSet(player->getPosition());
		}
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
			lpSoundMng.OnceSoundPlay("sound/jump.ckb");
			this->scheduleOnce(schedule_selector(GameScene::NextScene), 2.0f);
		}
	}
	if (attack != nullptr && score != nullptr)
	{
		enGenerate = map->GetEnemyCt();
		itemCt = map->GetItemCt();
		// プレイヤーとの判定
		enGenerate->Update(delta, player, score);
		itemCt->Update(delta, player, score);
	}
}

void GameScene::NextScene(float millsecond)
{
	auto scene = ResultScene::createScene();
	if (scene != nullptr)
	{
		auto director = cocos2d::Director::getInstance();
		director->replaceScene(scene);
	}
}

void GameScene::visitor(cocos2d::Renderer * renderer, const cocos2d::Mat4 & parentTransform, uint32_t parentFlags)
{
	lpEffectMng.GetEffectManager()->begin(renderer, _globalZOrder);
	Scene::visit(renderer, parentTransform, parentFlags);
	lpEffectMng.GetEffectManager()->end(renderer, _globalZOrder);
}

