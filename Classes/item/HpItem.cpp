#include "HpItem.h"

USING_NS_CC;

Sprite * HpItem::createHpItem(const char* fileName)
{
	return HpItem::create(fileName);
}

HpItem::HpItem()
{
}


HpItem::~HpItem()
{
}

void HpItem::Init()
{
}
