#include "TitleScene.h"
#include "GameScene.h"
#include "input/OPRT_Touch.h"
#define FLASHING_TIME 60

USING_NS_CC;

TitleScene::TitleScene()
{
	Init();
}

TitleScene::~TitleScene()
{
	clickUI->release();
}

void TitleScene::Init()
{
	auto bgBackLayer = Layer::create();
	bgBackLayer->setName("BG_BACKGROUND");
	this->addChild(bgBackLayer, BG_BACK);
	Sprite* background = Sprite::create("image/Environment/school.jpg");
	background->setName("TitleBack");
	//background->setScale(0.8f, 0.65f);
	background->setAnchorPoint(cocos2d::Vec2(0, 0));
	bgBackLayer->addChild(background, BG_BACK);

	clickUI = Sprite::create("image/Environment/click.png");
	clickUI->setName("click");
	clickUI->setScale(0.5f, 0.5f);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	clickUI->setPosition(cocos2d::Vec2(visibleSize.width / 2, 100));
	bgBackLayer->addChild(clickUI, BG_BACK);

	time = 0;
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
	time++;
	if ((time * (1 - flam) >= 0) && (time * (1 - flam) < FLASHING_TIME))
	{
		clickUI->setScale(0.5f, 0.5f);
	}
	else if((time * (1 - flam) >= 60) && (time * (1 - flam) < FLASHING_TIME * 2))
	{
		clickUI->setScale(0, 0);
	}
	else
	{
		time = 0;
	}

	//lpSoundMng.Update();
	auto data = oprt_state->GetData();
	oprt_state->Update();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (data.key.first != EventKeyboard::KeyCode::KEY_ENTER &&
		data.key.second == EventKeyboard::KeyCode::KEY_ENTER)
	{
		//sound->stop();
		//sound->destroy();
		NextScene();
	}
#else
	if (data.key.first != EventKeyboard::KeyCode::KEY_SPACE &&
		data.key.second == EventKeyboard::KeyCode::KEY_SPACE)
	{
		//sound->stop();
		//sound->destroy();
		NextScene();
	}
#endif
	
}

void TitleScene::NextScene()
{
	auto scene = GameScene::createScene();
	TransitionFade* fade = TransitionFade::create(1.0f, scene, Color3B::WHITE);
	auto director = cocos2d::Director::getInstance();
	director->replaceScene(fade);
}
