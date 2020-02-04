#pragma once
#include "cocos2d.h"

class DashFx : public cocos2d::Sprite
{
public:
	static DashFx* createDash();			//�N���X�𐶐�
	DashFx();
	~DashFx();
	void SetAddAnim(std::string fileName);
	void update(float delta);
	CREATE_FUNC(DashFx);
private:
	float time;
};

