#include "TitleScene.h"
#include "GameScene.h"
#include "ui/clickUI.h"
#include "ui/TitleNameMove.h"
#include "ui/BackScroll.h"
#include "sound/SoundMng.h"
#include "sound/SoundSafeRelese.h"

#include "Glass.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "input/OPRT_Key.h"
#else
#include "input/OPRT_Touch.h"
#endif

USING_NS_CC;

TitleScene::TitleScene()
{
	sound = nullptr;
	Init();
}

TitleScene::~TitleScene()
{
	if (_running)
	{
		onExit();
	}
	SoundSafeRelese()(sound);
}

cocos2d::Scene * TitleScene::createScene()
{
	return TitleScene::create();
}

void TitleScene::Init()
{
	// レイヤー追加
	auto bgBackLayer = Layer::create();
	bgBackLayer->setName("BG_BACKGROUND");
	this->addChild(bgBackLayer, BG_BACK);

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

	visibleSize = Director::getInstance()->getVisibleSize();

	//タイトル表示＋演出準備
	auto titleName = TitleNameMove::create();
	if (titleName != nullptr)
	{
		titleName->Init(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f), Vec2(1.5f, 1.5f), bgBackLayer);
	}

	//クリックUI表示
	click = ClickUI::createClick();
	if (click != nullptr)
	{
		click->Init(Vec2(visibleSize.width / 2.0f, 200.0f), Vec2(1.0f, 1.0f), bgBackLayer);
	}

	auto glass = Glass::create();
	this->addChild(glass, 0);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	oprt_state.reset(new OPRT_Key(this));
#else
	oprt_state.reset(new OPRT_Touch(this));
#endif

	sound = lpSoundMng.SoundLoopPlay("sound/TitleScene.ckb");

	this->setName("Title");
	this->scheduleUpdate();
}

void TitleScene::update(float delta)
{
	lpSoundMng.Update();
	oprt_state->Update();

	for (auto bg : backSrl)
	{
		if (bg != nullptr)
		{
			bg->ScrBackSet(visibleSize / 2.0f);
		}
	}

	data = oprt_state->GetData();
	auto CheckClick = [this](EventKeyboard::KeyCode key)
	{
		if (data.key.first != key &&
			data.key.second == key)
		{
			NextScene();
		}
	};
	CheckClick(EventKeyboard::KeyCode::KEY_A);
	CheckClick(EventKeyboard::KeyCode::KEY_S);
}

bool TitleScene::NextScene()
{
	auto scene = GameScene::createScene();
	if (scene != nullptr)
	{
		TransitionFadeBL* fade = TransitionFadeBL::create(1.0f, scene);
		auto director = cocos2d::Director::getInstance();
		if (fade != nullptr)
		{
			director->replaceScene(fade);
		}
		else
		{
			// TransitionFadeBLのcreateで失敗した場合はそのままsceneをreplaceする
			director->replaceScene(scene);
		}
		return true;
	}
	// アサート出す
	return false;
}
