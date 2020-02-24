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

	bool AddModule(std::string str, actModule& module);  //���[�J���ϐ�mapAct�ɃA�N�V��������ǉ����Ă���
	void MoveModule(input_data data, float delta);  //���������s����

private:
	std::map<std::string, actModule> mapAct;//�A�N�V�����̏��Ǘ�
	std::string animName;
	cocos2d::Action* plNowAct;
	cocos2d::Action* enNowAct;	
	Unit* unit;
};