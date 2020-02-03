#include "DashFx.h"
#include "../Animation/AnimCtl.h"

USING_NS_CC;

DashFx * DashFx::createDash()
{
	return DashFx::create();
}

DashFx::DashFx()
{
	deathFlag = false;
	lpAnimCtl.AddAnimation("player", "dash-a", 0.1f);
	lpAnimCtl.AddAnimation("player", "dash-b", 0.1f);

	lpAnimCtl.RunAnimation(this, "player-dash-b", -1, 0);
}


DashFx::~DashFx()
{
}

void DashFx::SetDeathFlag(bool flag)
{
	deathFlag = flag;
}

bool DashFx::GetDeathFlag()
{
	return deathFlag;
}
