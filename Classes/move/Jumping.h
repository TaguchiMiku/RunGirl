#pragma once
#include "cocos2d.h"


struct actModule;
struct Jumping
{
	//�W�����v����
	bool operator()(cocos2d::Sprite& sp, actModule& module);
};

