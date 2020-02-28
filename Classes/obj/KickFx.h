#pragma once
#include "cocos2d.h"

class Player;
class KickFx : public cocos2d::Sprite
{
public:
	KickFx();
	~KickFx();
	static KickFx* createKick();
	void Init(std::string animName, cocos2d::Vec2 position, cocos2d::Vec2 scale, cocos2d::Layer* layer);
	void SetAddAnim(std::string animName);
	void Update(Player* player);
	CREATE_FUNC(KickFx);
private:
	float scale;
};
