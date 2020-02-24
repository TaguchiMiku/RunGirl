#pragma once
#include "cocos2d.h"
#include "Item.h"

class FxGlow : public Item
{
public:
	static FxGlow* createHpItem();
	FxGlow();
	~FxGlow();
	void SetDeathFlag(bool flag)override;
	bool GetDeathFlag()override;
	CREATE_FUNC(FxGlow);
};

