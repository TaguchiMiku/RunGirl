#include "CheckKey.h"
#include "actModule.h"
#include "effect/EffectMng.h"

USING_NS_CC;

bool CheckKey::operator()(Sprite& sp, actModule& module)
{
	if ((module.nowKey != module.oldKey) && (module.nowKey == module.keyCode))
	{
		return true;
	}
	if ((module.nowKey == module.oldKey) && (module.nowKey == module.keyCode))
	{
		return true;
	}
	return false;
}
