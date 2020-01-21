#pragma once
#include "cocos2d.h"
#include "input/OPRT_State.h"

//#include "sound/SoundMng.h"

class clickUI;
class TitleNameMove;
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
	//CkSound* sound;
};

