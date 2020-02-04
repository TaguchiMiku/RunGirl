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
#define LOCAL_SPACE 100
#define STRING_SIZE 35
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
	allScore = score;
	number = 0;
	anser = 0;
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

	auto candy = Sprite::create("image/Sprites/item/bonus1.png");
	candy->setPosition(Vec2(visibleSize.width / 2 - LOCAL_SPACE, visibleSize.height / 2 + 100));
	candy->setScale(0.7f, 0.7f);
	this->addChild(candy, 0);
	auto light = Sprite::create("image/Sprites/item/lightning.png");
	light->setPosition(Vec2(visibleSize.width / 2 - LOCAL_SPACE, visibleSize.height / 2 + 10));
	light->setScale(0.5f, 0.5f);
	this->addChild(light, 0);
	auto closs1 = Sprite::create("image/Sprites/item/peke.png");
	closs1->setPosition(Vec2(visibleSize.width / 2 - LOCAL_SPACE / 2, visibleSize.height / 2 + 100));
	this->addChild(closs1, 0);
	auto closs2 = Sprite::create("image/Sprites/item/peke.png");
	closs2->setPosition(Vec2(visibleSize.width / 2 - LOCAL_SPACE / 2, visibleSize.height / 2 + 10));
	this->addChild(closs2, 0);

	//画像読み込み（数字画像リスト）
	for (int num = 0; num < 10; num++)
	{
		numList[num] = "image/Sprites/numberC/_number_0" + std::to_string(num) + ".png";
	}
	//表示する座標リスト
	for (int j = 0; j < 3; j++)
	{
		rankPos[j] = Vec2(visibleSize.width / 2 + 35 * j, visibleSize.height / 2 + 100);
		rankPos2[j] = Vec2(visibleSize.width / 2 + 35 * j, visibleSize.height / 2 + 10);
	}
	//描画するスプライト情報リスト(1の位から順に)
	for (int rank = 0; rank < 3; rank++)
	{
		numberSpList[rank] = Sprite::create("image/Sprites/numberC/_number_00.png");
		numberSpList[rank]->setScale(0.3f, 0.3f);
		numberSpList[rank]->setPosition(rankPos[2 - rank]);
		this->addChild(numberSpList[rank], 1);
		numberSpListL[rank] = Sprite::create("image/Sprites/numberC/_number_00.png");
		numberSpListL[rank]->setScale(0.3f, 0.3f);
		numberSpListL[rank]->setPosition(rankPos2[2 - rank]);
		this->addChild(numberSpListL[rank], 1);
	}
	ItemCount();
	//スコア表示
	scorePtr = Score::createScore();
	visibleSize = Director::getInstance()->getVisibleSize();
	scorePtr->setScale(1.5f, 1.5f);
	scorePtr->setPosition(Vec2(visibleSize.width / 2 - 100, -this->getPosition().y - Director::getInstance()->getVisibleSize().height + STRING_SIZE * 2 + visibleSize.height / 2 - 100));
	this->addChild(scorePtr, 0);
	scorePtr->Init(bgBackLayer);
	scorePtr->DrawScore();
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

void ResultScene::ItemCount()
{
	// アイテム取得数の表示
	int cnt = 1;
	anser = scorePtr->GetCandy();
	for (auto numSp : numberSpList)
	{
		if (anser < 0)
		{
			break;
		}
		number = anser % 10;
		anser = anser / 10;
		numSp->setTexture(numList[number]);
		cnt += 10;
	}
	anser = scorePtr->GetLight();
	for (auto numSp : numberSpListL)
	{
		if (anser < 0)
		{
			break;
		}
		number = anser % 10;
		anser = anser / 10;
		numSp->setTexture(numList[number]);
		cnt += 10;
	}
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
