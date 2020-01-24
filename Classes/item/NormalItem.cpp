#include "NormalItem.h"

USING_NS_CC;

NormalItem * NormalItem::createNItem()
{
	return NormalItem::create();
}

NormalItem::NormalItem()
{
	deathFlag = false;
}


NormalItem::~NormalItem()
{
}

void NormalItem::SetDeathFlag(bool flag)
{
	deathFlag = flag;
}

bool NormalItem::GetDeathFlag()
{
	return deathFlag;
}
