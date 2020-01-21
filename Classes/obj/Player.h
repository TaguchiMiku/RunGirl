#pragma once
#include "cocos2d.h"
#include <memory>
#include <array>
#include <tuple>
#include "Animation/AnimCtl.h"
#include "../ActionCtl.h"
#include "../CameraCtl.h"
//using Info = std::array<cocos2d::Animation*, static_cast<int>(PLAYER_ST::MAX)>;//アニメーション情報、アニメーションの種類

enum TUPLE_INFO {
	VELOCITY,
	REVERCE,
	ANIMATE
};

class Player : public cocos2d::Sprite
{
public:
	static Player* createPlayer();			//クラスを生成
	Player();
	~Player();
	void update(float delta);				//毎フレーム更新関数
	void NextScene(float millsecond);
	void SetJumpSpeed(float speed);
	float GetJumpSpeed();
	void SetActState(ACT action);
	ACT GetActState();
	void SetGoalFlag(bool flag);
	bool GetGoalFlag();
	void SetAccelFlag(bool flag);
	bool GetAccelFlag();
	void SetAttackFlag(bool flag);
	bool GetAttackFlag();
	CREATE_FUNC(Player);

private:
	void AddActData();
	std::unique_ptr<CameraCtl> cameraCtl;
	std::unique_ptr<OPRT_State> oprt_state;	//入力クラスのメンバーを呼ぶ用のポインター
	std::unique_ptr<ActionCtl> actCtl;
	input_data data;						//入力されたデータを取り出す変数
	ACT nowAction;
	float jumpSpeed;
	cocos2d::Vec2 velocity;
	bool goalFlag;
	bool onceFlag;
	bool accelFlag;
	bool attackFlag;
	cocos2d::Action* action;//アニメーション情報を入れる
	float time;
};