#pragma once
#include "cocos2d.h"

struct actModule;
struct FallMove
{
	//重力落下初速設定
	bool operator()(actModule& module);
};

