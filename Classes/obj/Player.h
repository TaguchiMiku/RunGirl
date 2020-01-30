#pragma once
#include "Unit.h"
#include <memory>
#include <array>
#include <tuple>
#include "Animation/AnimCtl.h"
#include "../CameraCtl.h"
//using Info = std::array<cocos2d::Animation*, static_cast<int>(PLAYER_ST::MAX)>;//アニメーション情報、アニメーションの種類

enum TUPLE_INFO {
	VELOCITY,
	REVERCE,
	ANIMATE
};

class Player : public Unit
{
public:
	Player();
	~Player();
	Unit* createUnit()override;
	void Update(float delta)override;				//毎フレーム更新関数
	void SetTimeUpFlag(bool flag)override;
	void SetJumpSpeed(float speed)override;
	float GetJumpSpeed()override;
	void SetActState(ACT action)override;
	ACT GetActState()override;
	void SetAccelFlag(bool flag)override;
	bool GetAccelFlag()override;
	void SetAttackFlag(bool flag)override;
	bool GetAttackFlag()override;
	void SetSlowlyFlag(bool flag);
	float GetVelocityX()override;
	CREATE_FUNC(Player);

private:
	void AddActData();

	std::unique_ptr<CameraCtl> cameraCtl;
	std::unique_ptr<OPRT_State> oprt_state;	//入力クラスのメンバーを呼ぶ用のポインター
	std::unique_ptr<ActionCtl> actCtl;
	input_data data;						//入力されたデータを取り出す変数
	float time;
	float velocityX;
	bool slowlyFlag;
};