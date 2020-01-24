#pragma once
#include "cocos2d.h"

struct actModule;
struct CheckKey
{
	bool operator()(cocos2d::Sprite& sp, actModule& module);
};

