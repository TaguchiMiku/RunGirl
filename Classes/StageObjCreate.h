#pragma once
#include "cocos2d.h"

class StageObjCreate : public cocos2d::Sprite
{
public:
	static StageObjCreate* createStageObj();
	StageObjCreate();
	~StageObjCreate();
	void Init(std::string spName, cocos2d::Vec2 position, cocos2d::Vec2 scale, cocos2d::Layer* layer);
	void update(float delta);
	CREATE_FUNC(StageObjCreate);
private:
	cocos2d::Vec2 velocity;	// ‚Á”ò‚Ô‘¬“x
	bool blowOffFlag;		// ‚Á”ò‚Ô‚©‚Ç‚¤‚©‚ÌŠÇ—ƒtƒ‰ƒO
	float time;
};

