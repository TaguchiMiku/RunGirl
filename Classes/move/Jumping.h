#pragma once
#include "cocos2d.h"


struct actModule;
struct Jumping
{
	//ジャンプ処理
	bool operator()(cocos2d::Sprite& sp, actModule& module);
};

