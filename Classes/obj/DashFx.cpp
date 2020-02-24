#include "DashFx.h"
#include "../Animation/AnimCtl.h"
#define DASH_FX_LIMIT 1.0f

USING_NS_CC;

DashFx * DashFx::createDash()
{
	return DashFx::create();
}

DashFx::DashFx()
{
	Init();
}


DashFx::~DashFx()
{
}

void DashFx::Init()
{
	time = 0.0f;
	this->scheduleUpdate();
}

void DashFx::SetAddAnim(std::string fileName)
{
	lpAnimCtl.AddAnimation("player", fileName, 0.1f);
	lpAnimCtl.RunAnimation(this, "player-" + fileName, 1, 0);
}

void DashFx::update(float delta)
{
	time += delta;
	if (time > DASH_FX_LIMIT)
	{
		this->removeFromParentAndCleanup(true);
	}
}
