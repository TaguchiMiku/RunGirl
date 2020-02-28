#include "PointUpItem.h"

USING_NS_CC;

PointUpItem * PointUpItem::createHpItem()
{
	return PointUpItem::create();
}

PointUpItem::PointUpItem()
{
	Init();
}

PointUpItem::~PointUpItem()
{
}

void PointUpItem::Init()
{
	deathFlag = false;
	this->scheduleUpdate();
}

void PointUpItem::update(float delta)
{

}

void PointUpItem::SetDeathFlag(bool flag)
{
	deathFlag = flag;
}

bool PointUpItem::GetDeathFlag()
{
	return deathFlag;
}
