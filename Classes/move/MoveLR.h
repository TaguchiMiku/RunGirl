#pragma once
#include "cocos2d.h"

struct actModule;
struct MoveLR
{
	//左右移動処理
	bool operator()(actModule& module);
};

