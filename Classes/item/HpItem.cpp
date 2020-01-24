#include "HpItem.h"

USING_NS_CC;

HpItem * HpItem::createHpItem()
{
	return HpItem::create();
}

HpItem::HpItem()
{
	deathFlag = false;
}


HpItem::~HpItem()
{
}

void HpItem::SetDeathFlag(bool flag)
{
	deathFlag = flag;
}

bool HpItem::GetDeathFlag()
{
	return deathFlag;
}
