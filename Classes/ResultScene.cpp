#include "ResultScene.h"
#include "GameScene.h"
#include "ui/clickUI.h"
#include "Score.h"
#include "ui/BackScroll.h"
#include "sound/SoundMng.h"
#include "sound/SoundSafeRelese.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "input/OPRT_Key.h"
#else
#include "input/OPRT_Touch.h"
#endif
#define LOCAL_SPACE 100.0f
#define STRING_SIZE 35.0f
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
	SoundSafeRelese()(sound);
}

cocos2d::Scene * ResultScene::createScene()
{
	return ResultScene::create();
}

void ResultScene::Init()
{
	allScore = score;
	number = 0;
	anser = 0;
	time = 0.0f;

	// ラムダと範囲for文
	// 各得点等のレイヤー
	auto bgBackLayer = Layer::create();
	bgBackLayer->setName("BG_BACKGROUND");
	this->addChild(bgBackLayer, BG_BACK);

	auto LayerAdd = [this](std::string name, bool visible, float second)
	{
		auto layer = Layer::create();
		layer->setName(name);
		layer->setVisible(visible);
		this->addChild(layer, 1);
		resutLayer.emplace(name, std::make_pair(layer, second));
	};

	LayerAdd("RESULT_LAYER", false, 0.0f);
	LayerAdd("CANDY_LAYER", false, 1.0f);
	LayerAdd("LIGHT_LAYER", false, 2.0f);
	LayerAdd("SCORE_LAYER", false, 3.0f);
	LayerAdd("CLICK_UI_LAYER", false, 3.5f);

	visibleSize = Director::getInstance()->getVisibleSize();
	//背景追加
	auto backGround1 = BackScroll::create();
	if (backGround1 != nullptr)
	{
		backGround1->Init("Clouds_4", Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f), bgBackLayer, 0.05f);
		backSrl.emplace_back(backGround1);
	}
	auto backGround2 = BackScroll::create();
	if (backGround1 != nullptr)
	{
		backGround2->Init("Clouds_3", Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f), bgBackLayer, 0.1f);
		backSrl.emplace_back(backGround2);
	}
	// 薄い黒背景
	Rect rect = Rect( 0.0f, 0.0f, 500.0f, 500.0f );
	auto blackBG = Sprite::create();
	blackBG->setTextureRect( rect );
	blackBG->setColor(Color3B(0.0f, 0.0f, 0.0f));
	blackBG->setOpacity(128);
	blackBG->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
    this->addChild(blackBG, 0);

	auto SpriteAdd = [this](std::string fileName, Vec2 position, Vec2 scale, Layer* layer)
	{
		auto sp = Sprite::create(fileName);
		sp->setPosition(position);
		sp->setScale(scale.x, scale.y);
		layer->addChild(sp, 0);
	};

	// リザルト表示用スプライト
	SpriteAdd("image/Environment/Result.png", Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 200.0f), Vec2(0.7f, 0.7f), resutLayer["RESULT_LAYER"].first);
	SpriteAdd("image/Sprites/item/bonus1.png", Vec2(visibleSize.width / 2.0f - LOCAL_SPACE, visibleSize.height / 2.0f + 100.0f), Vec2(0.7f, 0.7f), resutLayer["CANDY_LAYER"].first);
	SpriteAdd("image/Sprites/item/lightning.png", Vec2(visibleSize.width / 2.0f - LOCAL_SPACE, visibleSize.height / 2.0f + 10.0f), Vec2(0.5f, 0.5f), resutLayer["LIGHT_LAYER"].first);
	SpriteAdd("image/Sprites/item/peke.png", Vec2(visibleSize.width / 2.0f - LOCAL_SPACE / 3.0f, visibleSize.height / 2.0f + 100.0f), Vec2(1.0f, 1.0f), resutLayer["CANDY_LAYER"].first);
	SpriteAdd("image/Sprites/item/peke.png", Vec2(visibleSize.width / 2.0f - LOCAL_SPACE / 3.0f, visibleSize.height / 2.0f + 10.0f), Vec2(1.0f, 1.0f), resutLayer["LIGHT_LAYER"].first);

	//画像読み込み（数字画像リスト）
	for (int num = 0; num < 10; num++)
	{
		numList[num] = "image/Sprites/numberC/_number_0" + std::to_string(num) + ".png";
	}
	//表示する座標リスト
	for (float j = 0; j < 3.0f; j++)
	{
		rankPos[j] = Vec2(visibleSize.width / 2.0f + STRING_SIZE + STRING_SIZE * j, visibleSize.height / 2.0f + 100.0f);
		rankPos2[j] = Vec2(visibleSize.width / 2.0f + STRING_SIZE + STRING_SIZE * j, visibleSize.height / 2.0f + 10.0f);
	}
	//描画するスプライト情報リスト(1の位から順に)
	for (int rank = 0; rank < 3; rank++)
	{
		numberSpList[rank] = Sprite::create("image/Sprites/numberC/_number_00.png");
		numberSpList[rank]->setScale(0.3f, 0.3f);
		numberSpList[rank]->setPosition(rankPos[2 - rank]);
		resutLayer["CANDY_LAYER"].first->addChild(numberSpList[rank], 1);
		numberSpListL[rank] = Sprite::create("image/Sprites/numberC/_number_00.png");
		numberSpListL[rank]->setScale(0.3f, 0.3f);
		numberSpListL[rank]->setPosition(rankPos2[2 - rank]);
		resutLayer["LIGHT_LAYER"].first->addChild(numberSpListL[rank], 1);
	}
	ItemCount();
	//スコア表示
	auto scoreSp = Sprite::create("image/Environment/Score.png");
	scoreSp->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - STRING_SIZE - STRING_SIZE / 2.0f));
	scoreSp->setScale(0.2f, 0.2f);
	resutLayer["SCORE_LAYER"].first->addChild(scoreSp, 0);

	visibleSize = Director::getInstance()->getVisibleSize();

	scorePtr = Score::createScore();
	scorePtr->setScale(1.5f, 1.5f);
	scorePtr->setPosition(Vec2(visibleSize.width / 2.0f - STRING_SIZE * 3.0f + 15.0f, -this->getPosition().y - Director::getInstance()->getVisibleSize().height + STRING_SIZE * 2.0f + visibleSize.height / 2.0f - 100.0f));
	resutLayer["SCORE_LAYER"].first->addChild(scorePtr, 0);
	scorePtr->Init(resutLayer["SCORE_LAYER"].first);
	scorePtr->DrawScore();

	//クリックUI表示
	click = ClickUI::createClick();
	if (click != nullptr)
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		click->Init(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 200.0f), Vec2(0.5f, 0.5f), resutLayer["CLICK_UI_LAYER"].first);
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

void ResultScene::update(float delta)
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

	// 結果を順に表示させていく
	time += delta;
	for (auto layer : resutLayer)
	{
		if (time > layer.second.second)
		{
			layer.second.first->setVisible(true);
		}
	}
}

// 次のシーンへ遷移させる
bool ResultScene::NextScene()
{
	auto scene = TitleScene::createScene();
	if (scene != nullptr)
	{
		TransitionFade* fade = TransitionFade::create(1.0f, scene, Color3B::WHITE);
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

// アイテム取得数を表示
void ResultScene::ItemCount()
{
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

