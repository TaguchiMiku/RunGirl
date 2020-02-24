#pragma once
#include "Unit.h"
#include <memory>
#include <array>
#include <tuple>
#include "Animation/AnimCtl.h"
#include "../CameraCtl.h"

enum TUPLE_INFO {
	VELOCITY,
	REVERCE,
	ANIMATE
};

class Score;
class Player : public Unit
{
public:
	Player();
	~Player();
	Unit* createUnit()override;
	void Init()override;
	void Update(float delta)override;
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
	void SetSlowlyFlag(bool flag);
	bool GetSlowlyFlag();
	CREATE_FUNC(Player);

private:
	void AddActData();

	std::unique_ptr<CameraCtl> cameraCtl;
	std::unique_ptr<OPRT_State> oprt_state;	//入力クラスのメンバーを呼ぶ用のポインター
	std::unique_ptr<ActionCtl> actCtl;
	input_data data;						//入力されたデータを取り出す変数
	float time;
	float dashFxTime;
	float velocityX;
	bool slowlyFlag;
};