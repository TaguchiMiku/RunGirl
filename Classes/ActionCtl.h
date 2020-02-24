#pragma once
#include "cocos2d.h"
#include "actModule.h"
#include "Animation/AnimCtl.h"
#include "input/OPRT_State.h"
#include <map>

enum INPUT_DATA{
	FIRST,
	SECOND,
	MAX
};

enum class ACT_TAG{
	NORMAL,
	ATTACK,
	MAX
};

class Unit;
class ActionCtl
{
public:
	ActionCtl();
	~ActionCtl();

	bool AddModule(std::string str, actModule& module);  //ローカル変数mapActにアクション情報を追加していく
	void MoveModule(input_data data, float delta);  //動きを実行する

private:
	std::map<std::string, actModule> mapAct;//アクションの情報管理
	std::string animName;
	cocos2d::Action* plNowAct;
	cocos2d::Action* enNowAct;	
	Unit* unit;
};