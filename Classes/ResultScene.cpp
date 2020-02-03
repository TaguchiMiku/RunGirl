#include "ResultScene.h"
#include "GameScene.h"
#include "ui/clickUI.h"
#include "Score.h"
#include "ui/BackScroll.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "input/OPRT_Key.h"
#include "sound/SoundMng.h"
#else
#include "input/OPRT_Touch.h"
#endif
USING_NS_CC;

ResultScene::ResultScene()
{
	Init();
}


ResultScene::~ResultScene()
{
	if (_running)
	{
		onExit();
	}
	//CkShutdown();
}

void ResultScene::Init()
{
	auto bgBackLayer = Layer::create();
	bgBackLayer->setName("BG_BACKGROUND");
	this->addChild(bgBackLayer, BG_BACK);
	visibleSize = Director::getInstance()->getVisibleSize();
	//背景追加
	auto backGround1 = BackScroll::create();
	if (backGround1 != nullptr)
	{
		backGround1->Init("Clouds_4", Vec2(0, 0), Vec2(1.0f, 1.0f), bgBackLayer, 0.05f);
		backSrl.emplace_back(backGround1);
	}
	auto backGround2 = BackScroll::create();
	if (backGround1 != nullptr)
	{
		backGround2->Init("Clouds_3", Vec2(0, 0), Vec2(1.0f, 1.0f), bgBackLayer, 0.1f);
		backSrl.emplace_back(backGround2);
	}
	//クリックUI表示
	click = clickUI::createClick();
	if (click != nullptr)
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		click->Init(Vec2(visibleSize.width / 2, 100), Vec2(0.5f, 0.5f), bgBackLayer);
	}

	//スコア表示
	score = Score::createScore();
	visibleSize = Director::getInstance()->getVisibleSize();
	score->setScale(1.5f, 1.5f);
	score->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height - 200));
	this->addChild(score, 0);
	score->Init(bgBackLayer);
	score->DrawScore();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	oprt_state.reset(new OPRT_Key(this));
#else
	oprt_state.reset(new OPRT_Touch(this));
#endif
	//sound = lpSoundMng.SoundLoopPlay("Resources/sound/titleBGM.ckb");
	this->setName("Result");
	this->scheduleUpdate();
}

cocos2d::Scene * ResultScene::createScene()
{
	return ResultScene::create();
}

void ResultScene::update(float flam)
{
	//lpSoundMng.Update();
	auto data = oprt_state->GetData();
	oprt_state->Update();

	for (auto bg : backSrl)
	{
		if (bg != nullptr)
		{
			bg->ScrBackSet(visibleSize / 2);
		}
	}

	if (data.key.first != EventKeyboard::KeyCode::KEY_A &&
		data.key.second == EventKeyboard::KeyCode::KEY_A)
	{
		//sound->stop();
		//sound->destroy();
		NextScene();
	}
	if (data.key.first != EventKeyboard::KeyCode::KEY_S &&
		data.key.second == EventKeyboard::KeyCode::KEY_S)
	{
		//sound->stop();
		//sound->destroy();
		NextScene();
	}

}

void ResultScene::NextScene()
{
	auto scene = TitleScene::createScene();
	TransitionFade* fade = TransitionFade::create(1.0f, scene, Color3B::WHITE);
	if (scene != nullptr)
	{
		auto director = cocos2d::Director::getInstance();
		director->replaceScene(fade);
	}
}
