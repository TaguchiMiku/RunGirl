#pragma once
#include "cocos2d.h"
#include "Item.h"

class PointUpItem : public Item
{
public:
	static PointUpItem* createHpItem();
	PointUpItem();
	~PointUpItem();
	void Init();
	void update(float delta);
	void SetDeathFlag(bool flag)override;
	bool GetDeathFlag()override;
	CREATE_FUNC(PointUpItem);
};

