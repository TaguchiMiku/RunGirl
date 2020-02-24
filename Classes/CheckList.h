#pragma once
#include "cocos2d.h"

struct actModule;
struct CheckList
{
	bool operator()(actModule& module);
};