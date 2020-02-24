#pragma once
#include "cocos2d.h"

struct actModule;
struct CheckKey
{
	bool operator()(actModule& module);
};

