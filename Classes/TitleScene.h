#pragma once
#include "cocos2d.h"
#include "input/OPRT_State.h"
#include <vector>
#include <memory>
#include <cricket-1.6.7/inc/ck/sound.h>
#include <cricket-1.6.7/inc/ck/bank.h>
#include <cricket-1.6.7/inc/ck/ck.h>

class ClickUI;
class TitleNameMove;
class BackScroll;

class TitleScene : public cocos2d::Scene
{
public:
	TitleScene();
	~TitleScene();
	static cocos2d::Scene* createScene();
	void Init();
	void update(float delta);
	bool NextScene();
	CREATE_FUNC(TitleScene);

private:
	std::unique_ptr<OPRT_State> oprt_state;
	ClickUI* click;
	CkSound* sound;
	input_data data;
	std::vector<BackScroll*> backSrl;
	cocos2d::Size visibleSize;
	TitleNameMove* titleName;
};