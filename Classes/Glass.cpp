#include "Glass.h"
#include "Animation/AnimCtl.h"

USING_NS_CC;

Glass::Glass()
{
	Init();
}

Glass::~Glass()
{
}

Glass * Glass::createGlass()
{
	return Glass::create();
}

void Glass::Init()
{
	setPosition(Vec2(100, 100));
	lpAnimCtl.AddAnimation("glass", "move", 0.05f);
	action = lpAnimCtl.RunAnimation(this, "glass-move", -1, 0);
}
