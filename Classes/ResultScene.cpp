#include "ResultScene.h"
#include "GameScene.h"
#include "input/OPRT_Touch.h"
#include "ui/clickUI.h"
#include "Score.h"
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

	//クリックUI表示
	click = clickUI::createClick();
	if (click != nullptr)
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		click->Init(Vec2(visibleSize.width / 2, 100), Vec2(0.5f, 0.5f), bgBackLayer);
	}

	//スコア表示
	score = Score::createScore();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	score->setScale(1.5f, 1.5f);
	score->setPosition(Vec2(visibleSize.width / 2 - score->getScaleX(), visibleSize.height));
	this->addChild(score, 0);
	score->Init(bgBackLayer);
	score->DrawScore();

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

void ResultScene::NextScene()
{
	auto scene = TitleScene::createScene();
	TransitionFade* fade = TransitionFade::create(1.0f, scene, Color3B::WHITE);
	auto director = cocos2d::Director::getInstance();
	director->replaceScene(fade);
}
