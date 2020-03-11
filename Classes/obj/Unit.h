#pragma once
#include "cocos2d.h"
#include "../ActionCtl.h"

class Unit : public cocos2d::Sprite
{
public:
	~Unit() {};
	virtual void SetTimeUpFlag(bool flag) = 0;
	virtual Unit* createUnit() = 0;
	virtual void Init() = 0;
	virtual void Update(float delta) = 0;
	virtual void SetJumpSpeed(float speed) = 0;
	virtual float GetJumpSpeed() = 0;
	virtual void SetActState(ACT action) = 0;
	virtual ACT GetActState() = 0;
	virtual void SetAccelFlag(bool flag) = 0;
	virtual bool GetAccelFlag() = 0;
	virtual void SetAttackFlag(bool flag) = 0;
	virtual bool GetAttackFlag() = 0;
	virtual float GetVelocityX() = 0;
	virtual void SetBigModeFlag(bool flag) = 0;
	virtual bool GetBigModeFlag() = 0;

protected:
	ACT nowAction;		// ���݂̓���
	float jumpSpeed;	// �W�����v���x
	bool attackFlag;	// �U������t���O
	bool accelFlag;		// ��������t���O
	bool timeUpFlag;	// �^�C���A�b�v�t���O
	bool bigModeFlag;	// ���剻�p�t���O
};

