#pragma once
#include "cocos2d.h"

struct actModule;
struct JumpMove
{
	//ジャンプの初速度設定
	bool operator()(actModule& module);
};

