#pragma once
#include "cocos2d.h"
#include "TitleScene.h"
#include <array>
#include <map>

class ClickUI;
class Score;
class BackScroll;

class ResultScene : public cocos2d::Scene
{
public:
	ResultScene();
	~ResultScene();
	static cocos2d::Scene* createScene();
	void Init();
	void update(float delta);
	bool NextScene();						// 次のシーンへ遷移させる
	void ItemCount();						// アイテム取得数を表示
	CREATE_FUNC(ResultScene);

private:
	std::unique_ptr<OPRT_State> oprt_state;
	ClickUI* click;
	CkSound* sound;
	input_data data;
	std::vector<BackScroll*> backSrl;
	Score* scorePtr;
	cocos2d::Size visibleSize;
	int allScore;
	std::array<cocos2d::Sprite*, 3> numberSpList;
	std::array<cocos2d::Sprite*, 3> numberSpListL;
	std::array<std::string, 10> numList;
	std::array<cocos2d::Vec2, 3> rankPos;	// キャンディー個数表示用　位のリスト
	std::array<cocos2d::Vec2, 3> rankPos2;  // 稲妻個数表示用　位のリスト
	std::map<std::string, std::pair<cocos2d::Layer*, float>> resutLayer;
	int number;
	int anser;
	float time;
};

