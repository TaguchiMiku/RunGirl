#include "TitleScene.h"
#include "GameScene.h"
#include "input/OPRT_Touch.h"
#include "ui/clickUI.h"
#include "ui/TitleNameMove.h"

USING_NS_CC;

TitleScene::TitleScene()
{
	Init();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	auto bgBackLayer = Layer::create();
	bgBackLayer->setName("BG_BACKGROUND");
	this->addChild(bgBackLayer, BG_BACK);
	Sprite* background = Sprite::create("image/Environment/school.png");
	background->setName("TitleBack");
	background->setScale(1.05f, 1.02f);
	background->setAnchorPoint(cocos2d::Vec2(0, 0));
	bgBackLayer->addChild(background, BG_BACK);


	Size visibleSize = Director::getInstance()->getVisibleSize();

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

	oprt_state.reset(new OPRT_Touch(this));
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
	auto data = oprt_state->GetData();
	oprt_state->Update();

	if (data.key.first != EventKeyboard::KeyCode::KEY_ENTER &&
		data.key.second == EventKeyboard::KeyCode::KEY_ENTER)
	{
		//sound->stop();
		//sound->destroy();
		NextScene();
	}
	if (data.key.first != EventKeyboard::KeyCode::KEY_SPACE &&
		data.key.second == EventKeyboard::KeyCode::KEY_SPACE)
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
