#include "TitleScene.h"
#include "GameScene.h"
#include "ui/clickUI.h"
#include "ui/TitleNameMove.h"
#include "ui/BackScroll.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "input/OPRT_Key.h"
#include "sound/SoundMng.h"
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
	if (sound)
	{
		sound->destroy();
		sound = nullptr;
	}
}

void TitleScene::Init()
{
	auto bgBackLayer = Layer::create();
	bgBackLayer->setName("BG_BACKGROUND");
	this->addChild(bgBackLayer, BG_BACK);

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
	auto backGround3 = BackScroll::create();
	if (backGround3 != nullptr)
	{
		backGround3->Init("Clouds_2", Vec2(0, 0), Vec2(1.0f, 1.0f), bgBackLayer, 0.2f);
		backSrl.emplace_back(backGround3);
	}
	auto backGround4 = BackScroll::create();
	if (backGround1 != nullptr)
	{
		backGround4->Init("Clouds_1", Vec2(0, 100), Vec2(1.0f, 1.0f), bgBackLayer, 0.5f);
		backSrl.emplace_back(backGround4);
	}


	visibleSize = Director::getInstance()->getVisibleSize();

	//タイトル表示＋演出準備
	titleName = TitleNameMove::create();
	if (titleName != nullptr)
	{
		titleName->Init(Vec2(visibleSize.width / 2 + 32, visibleSize.height / 2), Vec2(1.05f, 1.02f), bgBackLayer);
	}

	//クリックUI表示
	click = clickUI::createClick();
	if (click != nullptr)
	{
		click->Init(Vec2(visibleSize.width / 2, 100), Vec2(0.5f, 0.5f), bgBackLayer);
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	oprt_state.reset(new OPRT_Key(this));
	CkBank* bank = CkBank::newBank("Resources/sound/titleBGM.ckb");
#else
	oprt_state.reset(new OPRT_Touch(this));
	CkBank* bank = CkBank::newBank("sound/titleBGM.ckb");
#endif
	sound = CkSound::newBankSound(bank, 0);
	sound->setLoopCount(-1);
	sound->play();
	//sound = lpSoundMng.SoundLoopPlay("Resources/sound/titleBGM.ckb");
	this->setName("Title");
	this->scheduleUpdate();
}

cocos2d::Scene * TitleScene::createScene()
{
	return TitleScene::create();
}

void TitleScene::update(float flam)
{
	//lpSoundMng.Update();
	CkUpdate();
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

void TitleScene::NextScene()
{
	auto scene = GameScene::createScene();
	TransitionFadeBL* fade = TransitionFadeBL::create(1.0f, scene);
	if (scene != nullptr)
	{
		auto director = cocos2d::Director::getInstance();
		director->replaceScene(fade);
	}
}
