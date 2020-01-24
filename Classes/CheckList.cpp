#include "CheckList.h"
#include "obj/Player.h"
#include "obj/Enemy.h"

USING_NS_CC;

bool CheckList::operator()(Sprite & sp, actModule & module)
{
	if (module.sprite->getName() == "Player")
	{
		auto player = static_cast<Player*>(module.sprite);
		for (auto black : module.blackList)
		{
			if (black == player->GetActState())
			{
				return false;
			}
		}
		for (auto white : module.whiteList)
		{
			if (white == player->GetActState())
			{
				return true;
			}
		}
	}
	if (module.sprite->getName() == "Enemy")
	{
		auto enemy = static_cast<Enemy*>(module.sprite);
		for (auto black : module.blackList)
		{
			if (black == enemy->GetActState())
			{
				return false;
			}
		}
		for (auto white : module.whiteList)
		{
			if (white == enemy->GetActState())
			{
				return true;
			}
		}
	}

	if (module.whiteList.size() > 0)
	{
		return false;
	}
	return true;
}
