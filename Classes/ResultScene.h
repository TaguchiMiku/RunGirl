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
	std::array<cocos2d::Vec2, 3> rankPos;
	std::array<cocos2d::Vec2, 3> rankPos2;
	int number;
	int anser;
	//CkSound* sound;
};

