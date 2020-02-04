#pragma once
#include "cocos2d.h"
#include "TitleScene.h"

class clickUI;
class Score;
class BackScroll;
class ResultScene : public cocos2d::Scene
{
public:
	ResultScene();
	~ResultScene();
	void Init();
	CREATE_FUNC(ResultScene);
	static cocos2d::Scene* createScene();
	void ItemCount();
	void update(float flam);
	void NextScene();

private:
	std::unique_ptr<OPRT_State> oprt_state;
	clickUI* click;
	std::vector<BackScroll*> backSrl;
	Score* scorePtr;
	cocos2d::Size visibleSize;
	int allScore;
	std::array<cocos2d::Sprite*, 3> numberSpList;
	std::array<cocos2d::Sprite*, 3> numberSpListL;
	std::array<std::string, 10> numList;
	std::array<cocos2d::Vec2, 3> rankPos;	// キャンディー個数表示用　位のリスト
	std::array<cocos2d::Vec2, 3> rankPos2;  // 稲妻個数表示用　位のリスト
	cocos2d::Layer* candyLayer;
	cocos2d::Layer* lightLayer;
	cocos2d::Layer* scoreLayer;
	cocos2d::Layer* clickUILayer;
	int number;
	int anser;
	float time;
	CkSound* sound;
};

