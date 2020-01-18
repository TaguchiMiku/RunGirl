#include "ResultScene.h"
#include "GameScene.h"
#include "input/OPRT_Touch.h"
USING_NS_CC;

ResultScene::ResultScene()
{
	Init();
}


ResultScene::~ResultScene()
{
	//CkShutdown();
}

void ResultScene::Init()
{
	auto bgBackLayer = Layer::create();
	bgBackLayer->setName("BG_BACKGROUND");
	this->addChild(bgBackLayer, BG_BACK);
	cocos2d::Sprite* background = Sprite::create("image/Environment/middleground.png");
	background->setName("ResultBack");
	background->setAnchorPoint(cocos2d::Vec2(0, 0));
	bgBackLayer->addChild(background, BG_BACK);

	oprt_state.reset(new OPRT_Touch(this));
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

void ResultScene::NextScene()
{
	auto scene = TitleScene::createScene();
	TransitionFade* fade = TransitionFade::create(1.0f, scene, Color3B::WHITE);
	auto director = cocos2d::Director::getInstance();
	director->replaceScene(fade);
}
