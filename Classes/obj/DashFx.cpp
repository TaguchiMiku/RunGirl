#include "DashFx.h"
#include "../Animation/AnimCtl.h"
#define LIMIT 1

USING_NS_CC;

DashFx * DashFx::createDash()
{
	return DashFx::create();
}

DashFx::DashFx()
{
	time = 0.0f;
	this->scheduleUpdate();
}


DashFx::~DashFx()
{
	int a = 0;
}

void DashFx::SetAddAnim(std::string fileName)
{
	lpAnimCtl.AddAnimation("player", fileName, 0.1f);
	lpAnimCtl.RunAnimation(this, "player-" + fileName, 1, 0);
}

void DashFx::update(float delta)
{
	time += delta;
	if (time > LIMIT)
	{
		this->removeFromParentAndCleanup(true);
	}
}
