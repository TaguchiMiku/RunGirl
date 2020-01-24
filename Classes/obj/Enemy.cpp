﻿#include "Enemy.h"
#include "Animation/AnimCtl.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "input/OPRT_Key.h"
#include "../debug/_DebugConOut.h"
#include "../debug/_DebugDispOut.h"
#else
#include "input/OPRT_Touch.h"
#endif

USING_NS_CC;
#pragma execution_charactor_set("utf-8");

Enemy * Enemy::createEnemy()
{
	return Enemy::create();
}

Enemy::Enemy()
{
	lpAnimCtl.AddAnimation("player", "idle", 0.05f);
	lpAnimCtl.AddAnimation("enemy", "run", 0.05f);
	lpAnimCtl.AddAnimation("enemy", "jump", 0.05f);
	lpAnimCtl.RunAnimation(this, "player-idle", -1);
	deathFlag = false;
	this->setName("Enemy");
	jumpSpeed = 0;
	nowAction = ACT::IDLE;
	AddActData();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	oprt_state.reset(new OPRT_Key(this));
#else
	oprt_state.reset(new OPRT_Touch(this));
#endif
	scheduleUpdate();
}

Enemy::~Enemy()
{
}

void Enemy::update(float frame)
{
	if (getPositionX() <= 120)
	{
		return;
	}
	input_data data = oprt_state->GetData();
	data.key.first = EventKeyboard::KeyCode::KEY_NONE;
	data.key.second = EventKeyboard::KeyCode::KEY_NONE;
	oprt_state->Update();
	actCtl->MoveModule(data);
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

void Enemy::SetDeathFlag(bool flag)
{
	deathFlag = flag;
}

bool Enemy::GetDeathFlag()
{
	return deathFlag;
}

void Enemy::AddActData()
{
	actCtl.reset(new ActionCtl());
	{
		//左移動
		actModule actLeft;
		actLeft.velocity = Vec2(-5, 0);
		actLeft.reverce = true;
		actLeft.keyCode = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
		actLeft.animName = "enemy-run";
		actLeft.sprite = this;
		actLeft.offset = Vec2(-25, -110);
		actLeft.action = ACT::LEFT;
		actCtl->AddModule("左移動", actLeft);
	}
	{
		//右移動
		actModule actRight;
		actRight.velocity = Vec2(5, 0);
		actRight.reverce = false;
		actRight.keyCode = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
		actRight.animName = "enemy-run";
		actRight.sprite = this;
		actRight.offset = Vec2(25, -110);
		actRight.blackList.emplace_back(ACT::FALLING);
		actRight.blackList.emplace_back(ACT::JUMPING);
		actRight.action = ACT::RIGHT;
		actCtl->AddModule("右移動", actRight);
	}
	{
		//落下
		actModule actFall;
		actFall.velocity = Vec2(5, -1);
		actFall.reverce = false;
		actFall.keyCode = EventKeyboard::KeyCode::KEY_NONE;
		actFall.animName = "enemy-jump";
		actFall.sprite = this;
		actFall.offset = Vec2(-25, -120);
		actFall.blackList.emplace_back(ACT::JUMP);
		actFall.blackList.emplace_back(ACT::JUMPING);
		actFall.blackList.emplace_back(ACT::FALLING);
		actFall.action = ACT::FALL;
		actFall.jumpHeight = 0;
		actCtl->AddModule("落下", actFall);
	}
	{
		//落下中
		actModule actFalling;
		actFalling.velocity = Vec2(5, -1);
		actFalling.reverce = false;
		actFalling.keyCode = EventKeyboard::KeyCode::KEY_NONE;
		actFalling.animName = "enemy-jump";
		actFalling.sprite = this;
		actFalling.offset = Vec2(-25, -120);
		actFalling.blackList.emplace_back(ACT::JUMP);
		actFalling.blackList.emplace_back(ACT::JUMPING);
		actFalling.whiteList.emplace_back(ACT::FALL);
		actFalling.whiteList.emplace_back(ACT::FALLING);
		actFalling.action = ACT::FALLING;
		actFalling.gravity = 0.5f;
		actFalling.jumpHeight = 10;
		actCtl->AddModule("落下中", actFalling);
	}
	{
		//ジャンプ
		actModule actJump;
		actJump.velocity = Vec2(5, 0.2f);
		actJump.reverce = true;
		actJump.keyCode = EventKeyboard::KeyCode::KEY_SPACE;
		actJump.animName = "enemy-jump";
		actJump.sprite = this;
		actJump.offset = Vec2(-25, 120);
		actJump.blackList.emplace_back(ACT::FALL);
		actJump.blackList.emplace_back(ACT::FALLING);
		actJump.blackList.emplace_back(ACT::JUMPING);
		actJump.action = ACT::JUMP;
		actJump.jumpHeight = 10;
		actCtl->AddModule("ジャンプ", actJump);
	}
	{
		//ジャンプ中
		actModule actJumping;
		actJumping.velocity = Vec2(5, 0.5f);
		actJumping.reverce = true;
		actJumping.keyCode = EventKeyboard::KeyCode::KEY_SPACE;
		actJumping.animName = "player-jump";
		actJumping.sprite = this;
		actJumping.offset = Vec2(25, 120);
		actJumping.blackList.emplace_back(ACT::FALL);
		actJumping.blackList.emplace_back(ACT::FALLING);
		actJumping.whiteList.emplace_back(ACT::JUMP);
		actJumping.whiteList.emplace_back(ACT::JUMPING);
		actJumping.action = ACT::JUMPING;
		actJumping.gravity = 0.5f;
		actJumping.jumpHeight = 0;
		actCtl->AddModule("ジャンプ中", actJumping);
	}
}
