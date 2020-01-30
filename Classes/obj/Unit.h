#pragma once
#include "cocos2d.h"
#include "../ActionCtl.h"

class Unit : public cocos2d::Sprite
{
public:
	~Unit();
	virtual void SetTimeUpFlag(bool flag) = 0;
	virtual Unit* createUnit() = 0;
	virtual void Update(float delta) = 0;				//毎フレーム更新関数
	virtual void SetJumpSpeed(float speed) = 0;
	virtual float GetJumpSpeed() = 0;
	virtual void SetActState(ACT action) = 0;
	virtual ACT GetActState() = 0;
	virtual void SetAccelFlag(bool flag) = 0;
	virtual bool GetAccelFlag() = 0;
	virtual void SetAttackFlag(bool flag) = 0;
	virtual bool GetAttackFlag() = 0;
	virtual float GetVelocityX() = 0;

protected:
	ACT nowAction;
	float jumpSpeed;
	bool attackFlag;
	bool accelFlag;
	bool timeUpFlag;
};

