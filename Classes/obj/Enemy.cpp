#include "Enemy.h"
#include "input/OPRT_Enemy.h"
#include "Animation/AnimCtl.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "../debug/_DebugConOut.h"
#include "../debug/_DebugDispOutCC.h"
#else
#endif

USING_NS_CC;
#pragma execution_charactor_set("utf-8");

Enemy::Enemy()
{
	Init();
}

Enemy::~Enemy()
{
}

Unit * Enemy::createUnit()
{
	return Enemy::create();
}

void Enemy::Init()
{
	lpAnimCtl.AddAnimation("enemy", "run", 0.05f);
	lpAnimCtl.AddAnimation("enemy", "jump", 0.05f);
	lpAnimCtl.RunAnimation(this, "enemy-jump", -1, 0);
	deathFlag = false;
	moveFlag = false;
	this->setName("Enemy");
	jumpSpeed = 0.0f;
	nowAction = ACT::IDLE;
	accelFlag = false;
	attackFlag = false;
	timeUpFlag = false;
	bigModeFlag = false;
	velocityX = -3.0f;
	AddActData();

	//OPRT_Enemyを作る
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	oprt_state.reset(new OPRT_Enemy(this));
#else
	oprt_state.reset(new OPRT_Enemy(this));
#endif
	scheduleUpdate();
}

void Enemy::Update(float frame)
{
	if (timeUpFlag)
	{
		return;
	}
	if (getPositionX() <= 120.0f)
	{
		return;
	}
	//DEBUG_DrawRect("enBox", getPosition(), Vec2(-14.0f, 15.0f), Vec2(15.0f, -15.0f), Color4F(1.0f, 0.0f, 0.0f, 1.0f));
	oprt_state->Update();
	input_data data = oprt_state->GetData();
	actCtl->MoveModule(data, frame);
}

void Enemy::SetTimeUpFlag(bool flag)
{
	timeUpFlag = flag;
}

void Enemy::SetJumpSpeed(float speed)
{
	jumpSpeed = speed;
}

float Enemy::GetJumpSpeed()
{
	return jumpSpeed;
}

void Enemy::SetActState(ACT action)
{
	nowAction = action;
}

ACT Enemy::GetActState()
{
	return nowAction;
}

void Enemy::SetAccelFlag(bool flag)
{
	accelFlag = flag;
}

bool Enemy::GetAccelFlag()
{
	return accelFlag;
}

void Enemy::SetAttackFlag(bool flag)
{
	attackFlag = flag;
}

bool Enemy::GetAttackFlag()
{
	return attackFlag;
}

void Enemy::SetDeathFlag(bool flag)
{
	deathFlag = flag;
}

bool Enemy::GetDeathFlag()
{
	return deathFlag;
}

void Enemy::SetMoveFlag(bool flag)
{
	moveFlag = flag;
}

float Enemy::GetVelocityX()
{
	return velocityX;
}

void Enemy::SetBigModeFlag(bool flag)
{
	bigModeFlag = flag;
}

bool Enemy::GetBigModeFlag()
{
	return bigModeFlag;
}

void Enemy::AddActData()
{
	actCtl.reset(new ActionCtl());

	{
		//左移動
		actModule actLeft;
		actLeft.velocity = Vec2(velocityX, 0.0f);
		actLeft.reverce = true;
		actLeft.keyCode = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
		actLeft.animName = "enemy-run";
		actLeft.sprite = this;
		actLeft.offset.emplace_back(Vec2(-14.0f, 15.0f));
		actLeft.offset.emplace_back(Vec2(-14.0f, -14.0f));
		actLeft.blackList.emplace_back(ACT::FALLING);
		actLeft.blackList.emplace_back(ACT::JUMPING);
		actLeft.action = ACT::LEFT;
		actCtl->AddModule("左移動", actLeft);
	}
	{
		//落下
		actModule actFall;
		actFall.velocity = Vec2(0.0f, -1.0f);
		actFall.reverce = false;
		actFall.keyCode = EventKeyboard::KeyCode::KEY_NONE;
		actFall.animName = "enemy-jump";
		actFall.sprite = this;
		actFall.offset.emplace_back(Vec2(-14.0f, -14.0f));
		actFall.offset.emplace_back(Vec2(14.0f, -14.0f));
		actFall.blackList.emplace_back(ACT::JUMP);
		actFall.blackList.emplace_back(ACT::JUMPING);
		actFall.blackList.emplace_back(ACT::FALLING);
		actFall.action = ACT::FALL;
		actFall.jumpHeight = 0.0f;
		actCtl->AddModule("落下", actFall);
	}
	{
		//落下中
		actModule actFalling;
		actFalling.velocity = Vec2(velocityX, -1.0f);
		actFalling.reverce = false;
		actFalling.keyCode = EventKeyboard::KeyCode::KEY_NONE;
		actFalling.animName = "enemy-jump";
		actFalling.sprite = this;
		actFalling.offset.emplace_back(Vec2(-14.0f, -14.0f));
		actFalling.offset.emplace_back(Vec2(15.0f, -14.0f));
		actFalling.blackList.emplace_back(ACT::JUMP);
		actFalling.blackList.emplace_back(ACT::JUMPING);
		actFalling.whiteList.emplace_back(ACT::FALL);
		actFalling.whiteList.emplace_back(ACT::FALLING);
		actFalling.action = ACT::FALLING;
		actFalling.gravity = -0.5f;
		actFalling.jumpHeight = 10.0f;
		actCtl->AddModule("落下中", actFalling);
	}
	{
		//ジャンプ
		actModule actJump;
		actJump.velocity = Vec2(0.0f, 0.2f);
		actJump.reverce = true;
		actJump.keyCode = EventKeyboard::KeyCode::KEY_A;
		actJump.animName = "enemy-jump";
		actJump.sprite = this;
		actJump.offset.emplace_back(Vec2(-14.0f, 15.0f));
		actJump.offset.emplace_back(Vec2(15.0f, 15.0f));
		actJump.blackList.emplace_back(ACT::FALL);
		actJump.blackList.emplace_back(ACT::FALLING);
		actJump.blackList.emplace_back(ACT::JUMPING);
		actJump.action = ACT::JUMP;
		actJump.jumpHeight = 10.0f;
		actCtl->AddModule("ジャンプ", actJump);
	}
	{
		//ジャンプ中
		actModule actJumping;
		actJumping.velocity = Vec2(velocityX, 0.5f);
		actJumping.reverce = true;
		actJumping.keyCode = EventKeyboard::KeyCode::KEY_A;
		actJumping.animName = "enemy-jump";
		actJumping.sprite = this;
		actJumping.offset.emplace_back(Vec2(-14.0f, 15.0f));
		actJumping.offset.emplace_back(Vec2(15.0f, 15.0f));
		actJumping.blackList.emplace_back(ACT::FALL);
		actJumping.blackList.emplace_back(ACT::FALLING);
		actJumping.whiteList.emplace_back(ACT::JUMP);
		actJumping.whiteList.emplace_back(ACT::JUMPING);
		actJumping.action = ACT::JUMPING;
		actJumping.gravity = -0.5f;
		actJumping.jumpHeight = 0.0f;
		actCtl->AddModule("ジャンプ中", actJumping);
	}
	{
		//攻撃
		actModule actAttack;
		actAttack.velocity = Vec2(velocityX, 0.0f);
		actAttack.reverce = true;
		actAttack.keyCode = EventKeyboard::KeyCode::KEY_S;
		actAttack.animName = "enemy-jump";
		actAttack.sprite = this;
		actAttack.offset.emplace_back(Vec2(15.0f, 15.0f));
		actAttack.offset.emplace_back(Vec2(15.0f, -14.0f));
		actAttack.action = ACT::ATTACK;
		actAttack.blackList.emplace_back(ACT::FALLING);
		actAttack.blackList.emplace_back(ACT::JUMPING);
		actAttack.actionData = nullptr;
		actCtl->AddModule("攻撃", actAttack);
	}
}
