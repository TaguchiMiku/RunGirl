#include "SpeedUpItem.h"

USING_NS_CC;

SpeedUpItem * SpeedUpItem::createNItem()
{
	return SpeedUpItem::create();
}

SpeedUpItem::SpeedUpItem()
{
	Init();
}


SpeedUpItem::~SpeedUpItem()
{
}

void SpeedUpItem::Init()
{
	deathFlag = false;
	this->scheduleUpdate();
}

void SpeedUpItem::update(float delta)
{

}

void SpeedUpItem::SetDeathFlag(bool flag)
{
	deathFlag = flag;
}

bool SpeedUpItem::GetDeathFlag()
{
	return deathFlag;
}
