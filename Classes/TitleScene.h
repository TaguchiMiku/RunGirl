#pragma once
#include "cocos2d.h"
#include "input/OPRT_State.h"
#include <vector>
#include <cricket-1.6.7/inc/ck/sound.h>
#include <cricket-1.6.7/inc/ck/bank.h>
#include <cricket-1.6.7/inc/ck/ck.h>

//#include "sound/SoundMng.h"

class clickUI;
class TitleNameMove;
class BackScroll;
class TitleScene : public cocos2d::Scene
{
public:
	TitleScene();
	~TitleScene();
	void Init();
	CREATE_FUNC(TitleScene);
	static cocos2d::Scene* createScene();
	void update(float flam);
	void NextScene();

private:
	std::unique_ptr<OPRT_State> oprt_state;
	clickUI* click;
	TitleNameMove* titleName;
	CkSound* sound;
	std::vector<BackScroll*> backSrl;
	cocos2d::Size visibleSize;
};

