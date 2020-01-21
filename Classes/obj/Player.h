#pragma once
#include "cocos2d.h"
#include <memory>
#include <array>
#include <tuple>
#include "Animation/AnimCtl.h"
#include "../ActionCtl.h"
#include "../CameraCtl.h"
//using Info = std::array<cocos2d::Animation*, static_cast<int>(PLAYER_ST::MAX)>;//�A�j���[�V�������A�A�j���[�V�����̎��

enum TUPLE_INFO {
	VELOCITY,
	REVERCE,
	ANIMATE
};

class Player : public cocos2d::Sprite
{
public:
	static Player* createPlayer();			//�N���X�𐶐�
	Player();
	~Player();
	void update(float delta);				//���t���[���X�V�֐�
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
	std::unique_ptr<OPRT_State> oprt_state;	//���̓N���X�̃����o�[���Ăԗp�̃|�C���^�[
	std::unique_ptr<ActionCtl> actCtl;
	input_data data;						//���͂��ꂽ�f�[�^�����o���ϐ�
	ACT nowAction;
	float jumpSpeed;
	cocos2d::Vec2 velocity;
	bool goalFlag;
	bool onceFlag;
	bool accelFlag;
	bool attackFlag;
	cocos2d::Action* action;//�A�j���[�V������������
	float time;
};