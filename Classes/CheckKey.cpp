#include "CheckKey.h"
#include "actModule.h"
#include "effect/EffectMng.h"

USING_NS_CC;

bool CheckKey::operator()(actModule& module)
{
	return (module.nowKey == module.keyCode);
}
