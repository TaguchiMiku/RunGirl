#include "FxGlow.h"
#include "Animation/AnimCtl.h"

USING_NS_CC;

FxGlow * FxGlow::createHpItem()
{
	return FxGlow::create();
}

FxGlow::FxGlow()
{
	deathFlag = false;
	action = nullptr;
	lpAnimCtl.AddAnimation("Fx", "glow", 0.1f);
}


FxGlow::~FxGlow()
{
}

void FxGlow::SetDeathFlag(bool flag)
{
	deathFlag = flag;
}

bool FxGlow::GetDeathFlag()
{
	return deathFlag;
}
