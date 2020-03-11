#pragma once
#include "Unit.h"
#include "Animation/AnimCtl.h"
#include "../input/OPRT_State.h"

class Enemy :
	public Unit
{
public:
	Enemy();
	~Enemy();
	Unit* createUnit()override;
	void Init()override;
	void Update(float frame)override;
	void SetTimeUpFlag(bool flag)override;
	void SetJumpSpeed(float speed)override;
	float GetJumpSpeed()override;
	void SetActState(ACT action)override;
	ACT GetActState()override;
	void SetAccelFlag(bool flag)override;
	bool GetAccelFlag()override;
	void SetAttackFlag(bool flag)override;
	bool GetAttackFlag()override;
	float GetVelocityX()override;
	void SetBigModeFlag(bool flag)override;
	bool GetBigModeFlag()override;
	void SetDeathFlag(bool flag);
	bool GetDeathFlag();
	void SetMoveFlag(bool flag);

	CREATE_FUNC(Enemy);

private:
	void AddActData();

	std::unique_ptr<OPRT_State> oprt_state;	//入力クラスのメンバーを呼ぶ用のポインター
	std::unique_ptr<ActionCtl> actCtl;
	bool deathFlag;
	bool moveFlag;
	float velocityX;
};

