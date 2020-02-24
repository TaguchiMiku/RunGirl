#include "CheckList.h"
#include "obj/Player.h"
#include "obj/Enemy.h"

USING_NS_CC;

bool CheckList::operator()(actModule & module)
{
	auto unit = static_cast<Unit*>(module.sprite);
	for (auto black : module.blackList)
	{
		if (black == unit->GetActState())
		{
			return false;
		}
	}
	for (auto white : module.whiteList)
	{
		if (white == unit->GetActState())
		{
			return true;
		}
	}

	if (module.whiteList.size() > 0)
	{
		return false;
	}
	return true;
}
