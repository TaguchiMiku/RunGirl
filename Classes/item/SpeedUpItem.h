#pragma once
#include "cocos2d.h"
#include "Item.h"

class SpeedUpItem : public Item
{
public:
	static SpeedUpItem* createNItem();
	SpeedUpItem();
	~SpeedUpItem();
	void Init();
	void update(float delta);
	void SetDeathFlag(bool flag)override;
	bool GetDeathFlag()override;
	CREATE_FUNC(SpeedUpItem);
};

