#pragma once
#include "cocos2d.h"
#include "TitleScene.h"

class ResultScene : public cocos2d::Scene
{
public:
	ResultScene();
	~ResultScene();
	void Init();
	CREATE_FUNC(ResultScene);
	static cocos2d::Scene* createScene();
	void update(float flam);
	void NextScene();

private:
	std::unique_ptr<OPRT_State> oprt_state;
	//CkSound* sound;
};

