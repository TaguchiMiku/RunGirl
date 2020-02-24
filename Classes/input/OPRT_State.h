#pragma once
#include "cocos2d.h"
#include <array>
#include <utility>

enum class TYPE {
	KEY,
	TOUCH,
	MAX
};

enum class DIR {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	MAX
};

using INPUT_BTN = std::pair<cocos2d::EventKeyboard::KeyCode, cocos2d::EventKeyboard::KeyCode>;
using INPUT_ID = std::pair<cocos2d::EventKeyboard::KeyCode, cocos2d::EventKeyboard::KeyCode>;

struct input_data {
	INPUT_BTN key;		//nowとold情報
	INPUT_ID id;		//押された種類
	cocos2d::Vec2 pos;	//座標
};

struct OPRT_State : cocos2d::Node
{
	~OPRT_State() {};
	
	virtual TYPE GetType() = 0;
	virtual void Update() = 0;

	input_data GetData()
	{
		return data;
	}

protected:
	input_data data;	//入力データ保存用
};

