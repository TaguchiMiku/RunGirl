#pragma once
#include "cocos2d.h"

struct actModule;
struct FallMove
{
	//�d�͗��������ݒ�
	bool operator()(cocos2d::Sprite& sp, actModule& module);
};

