#include "ResultScene.h"
#include "GameScene.h"
#include "ui/clickUI.h"
#include "Score.h"
#include "ui/BackScroll.h"
#include "sound/SoundMng.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "input/OPRT_Key.h"
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
	if (sound)
	{
		sound->destroy();
	}
}

void ResultScene::Init()
{
	allScore = score;
	number = 0;
	anser = 0;
	time = 0;

	// 各得点等のレイヤー
	auto bgBackLayer = Layer::create();
	bgBackLayer->setName("BG_BACKGROUND");
	this->addChild(bgBackLayer, BG_BACK);

	candyLayer = Layer::create();
	candyLayer->setName("CANDY_LAYER");
	candyLayer->setVisible(false);
	this->addChild(candyLayer, 1);

	lightLayer = Layer::create();
	lightLayer->setName("LIGHT_LAYER");
	lightLayer->setVisible(false);
	this->addChild(lightLayer, 2);

	scoreLayer = Layer::create();
	scoreLayer->setName("SCORE_LAYER");
	scoreLayer->setVisible(false);
	this->addChild(scoreLayer, 3);

	clickUILayer = Layer::create();
	clickUILayer->setName("CLICK_UI_LAYER");
	clickUILayer->setVisible(false);
	this->addChild(clickUILayer, 3);

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
	// 薄い黒背景
	Rect rect = Rect( 0, 0, 500, 500 );
	auto blackBG = Sprite::create();
	blackBG->setTextureRect( rect );
	blackBG->setColor(Color3B(0.0f, 0.0f, 0.0f));
	blackBG->setOpacity(128);
	blackBG->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(blackBG, 0);
	// リザルト文字
	auto result = Sprite::create("image/Environment/Result.png");
	result->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 200));
	result->setScale(0.7f, 0.7f);
	this->addChild(result, 0);
	// キャンディーアイコン
	auto candy = Sprite::create("image/Sprites/item/bonus1.png");
	candy->setPosition(Vec2(visibleSize.width / 2 - LOCAL_SPACE, visibleSize.height / 2 + 100));
	candy->setScale(0.7f, 0.7f);
	candyLayer->addChild(candy, 0);
	// 稲妻アイコン
	auto light = Sprite::create("image/Sprites/item/lightning.png");
	light->setPosition(Vec2(visibleSize.width / 2 - LOCAL_SPACE, visibleSize.height / 2 + 10));
	light->setScale(0.5f, 0.5f);
	lightLayer->addChild(light, 0);
	// ×表記
	auto closs1 = Sprite::create("image/Sprites/item/peke.png");
	closs1->setPosition(Vec2(visibleSize.width / 2 - LOCAL_SPACE / 3, visibleSize.height / 2 + 100));
	candyLayer->addChild(closs1, 0);
	auto closs2 = Sprite::create("image/Sprites/item/peke.png");
	closs2->setPosition(Vec2(visibleSize.width / 2 - LOCAL_SPACE / 3, visibleSize.height / 2 + 10));
	lightLayer->addChild(closs2, 0);

	//画像読み込み（数字画像リスト）
	for (int num = 0; num < 10; num++)
	{
		numList[num] = "image/Sprites/numberC/_number_0" + std::to_string(num) + ".png";
	}
	//表示する座標リスト
	for (int j = 0; j < 3; j++)
	{
		rankPos[j] = Vec2(visibleSize.width / 2 + STRING_SIZE + STRING_SIZE * j, visibleSize.height / 2 + 100);
		rankPos2[j] = Vec2(visibleSize.width / 2 + STRING_SIZE + STRING_SIZE * j, visibleSize.height / 2 + 10);
	}
	//描画するスプライト情報リスト(1の位から順に)
	for (int rank = 0; rank < 3; rank++)
	{
		numberSpList[rank] = Sprite::create("image/Sprites/numberC/_number_00.png");
		numberSpList[rank]->setScale(0.3f, 0.3f);
		numberSpList[rank]->setPosition(rankPos[2 - rank]);
		candyLayer->addChild(numberSpList[rank], 1);
		numberSpListL[rank] = Sprite::create("image/Sprites/numberC/_number_00.png");
		numberSpListL[rank]->setScale(0.3f, 0.3f);
		numberSpListL[rank]->setPosition(rankPos2[2 - rank]);
		lightLayer->addChild(numberSpListL[rank], 1);
	}
	ItemCount();
	//スコア表示
	auto scoreSp = Sprite::create("image/Environment/Score.png");
	scoreSp->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - STRING_SIZE - STRING_SIZE / 2));
	scoreSp->setScale(0.2f, 0.2f);
	scoreLayer->addChild(scoreSp, 0);

	scorePtr = Score::createScore();
	visibleSize = Director::getInstance()->getVisibleSize();
	scorePtr->setScale(1.5f, 1.5f);
	scorePtr->setPosition(Vec2(visibleSize.width / 2 - STRING_SIZE * 3 + 15, -this->getPosition().y - Director::getInstance()->getVisibleSize().height + STRING_SIZE * 2 + visibleSize.height / 2 - 100));
	scoreLayer->addChild(scorePtr, 0);
	scorePtr->Init(scoreLayer);
	scorePtr->DrawScore();

	//クリックUI表示
	click = clickUI::createClick();
	if (click != nullptr)
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		click->Init(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 200), Vec2(0.5f, 0.5f), clickUILayer);
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	oprt_state.reset(new OPRT_Key(this));
#else
	oprt_state.reset(new OPRT_Touch(this));
#endif
	sound = lpSoundMng.SoundLoopPlay("sound/ResultScene.ckb");
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
	lpSoundMng.Update();
	auto data = oprt_state->GetData();
	oprt_state->Update();

	for (auto bg : backSrl)
	{
		if (bg != nullptr)
		{
			bg->ScrBackSet(visibleSize / 2);
		}
	}
	// 順に表示させていく
	time += flam;
	if (time > 1)
	{
		candyLayer->setVisible(true);
	}
	if (time > 2)
	{
		lightLayer->setVisible(true);
	}
	if (time > 3)
	{
		scoreLayer->setVisible(true);
	}
	if (time > 3.5f)
	{
		clickUILayer->setVisible(true);
	}

	if (data.key.first != EventKeyboard::KeyCode::KEY_A &&
		data.key.second == EventKeyboard::KeyCode::KEY_A)
	{
		NextScene();
	}
	if (data.key.first != EventKeyboard::KeyCode::KEY_S &&
		data.key.second == EventKeyboard::KeyCode::KEY_S)
	{
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
