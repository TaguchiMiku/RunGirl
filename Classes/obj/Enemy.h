#pragma once
#include "cocos2d.h"
#include "Animation/AnimCtl.h"
#include "../ActionCtl.h"
#include "input/OPRT_State.h"

class Enemy :
	public cocos2d::Sprite
{
public:
	static Enemy* createEnemy();		//Enemy�N���X�𐶐�
	Enemy();
	~Enemy();
	void update(float frame);
	void SetJumpSpeed(float speed);
	float GetJumpSpeed();
	void SetActState(ACT action);
	ACT GetActState();
	void SetDeathFlag(bool flag);
	bool GetDeathFlag();
	CREATE_FUNC(Enemy);

private:
	void AddActData();

	std::unique_ptr<OPRT_State> oprt_state;	//���̓N���X�̃����o�[���Ăԗp�̃|�C���^�[
	std::unique_ptr<ActionCtl> actCtl;
	ACT nowAction;
	float jumpSpeed;
	bool deathFlag;

};

