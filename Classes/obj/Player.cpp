﻿#include "Player.h"
#include "effect/EffectMng.h"
#include "../ResultScene.h"
#include "ui/CountDown.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "input/OPRT_Key.h"
#include "sound/SoundMng.h"
#include "../debug/_DebugConOut.h"
#include "../debug/_DebugDispOut.h"
#else
#include "input/OPRT_Touch.h"
#endif

USING_NS_CC;

#pragma execution_charactor_set("utf-8");

Player::Player()
{
	// 画面サイズと原点を取得
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin		 = Director::getInstance()->getVisibleOrigin();
	setPosition(Vec2(visibleSize.width / 2 + origin.x, 400 + origin.y));

	// アニメーションの初期化//シーンの先頭で読み込む
	lpAnimCtl.AddAnimation("player", "idle", 0.05f);
	lpAnimCtl.AddAnimation("player", "walk", 0.1f);
	lpAnimCtl.AddAnimation("player", "run", 0.05f);
	lpAnimCtl.AddAnimation("player", "jump", 0.05f);

	lpAnimCtl.RunAnimation(this, "player-idle", -1);

	// アクションデータを設定(追加)する
	AddActData();
	jumpSpeed = 0;
	nowAction = ACT::IDLE;
	accelFlag = false;
	attackFlag = false;
	timeUpFlag = false;
	time = 0;
	this->setName("Player");
	//lpSoundMng.Init();
// プラットフォーム別に入力クラス（操作の仕方）を切り替える
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	oprt_state.reset(new OPRT_Key(this));
#else
	oprt_state.reset(new OPRT_Touch(this));
#endif
	scheduleUpdate();
}

Player::~Player()
{
}

Unit * Player::createUnit()
{
	return Player::create();
}

//毎フレーム更新関数
void Player::Update(float delta)
{
	// 制限時間になったら止める
	if (timeUpFlag)
	{
		return;
	}

	// 加速する時間
	if (accelFlag)
	{
		time += delta;
		if (time >= 3.0f)
		{
			time = 0;
			accelFlag = false;
		}
	}

	// input処理とaction処理
	data = oprt_state->GetData();
	oprt_state->Update();
	actCtl->MoveModule(data);
	// 追従カメラ設定
	cameraCtl->FollowPlayer(Vec3(this->getPosition().x, this->getPosition().y, 500));
}

void Player::SetTimeUpFlag(bool flag)
{
	timeUpFlag = flag;
}

void Player::SetJumpSpeed(float speed)
{
	jumpSpeed = speed;
}

float Player::GetJumpSpeed()
{
	return jumpSpeed;
}

void Player::SetActState(ACT action)
{
	nowAction = action;
}

ACT Player::GetActState()
{
	return nowAction;
}

void Player::SetAccelFlag(bool flag)
{
	time = 0;
	accelFlag = flag;
}

bool Player::GetAccelFlag()
{
	return accelFlag;
}

void Player::SetAttackFlag(bool flag)
{
	attackFlag = flag;
}

bool Player::GetAttackFlag()
{
	return attackFlag;
}

void Player::AddActData()
{
	cameraCtl.reset(new CameraCtl());
	actCtl.reset(new ActionCtl());
	{
		//右移動
		actModule actRight;
		actRight.velocity = Vec2(5, 0);
		actRight.reverce = false;
		actRight.keyCode = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
		actRight.animName = "player-run";
		actRight.sprite = this;
		actRight.offset = Vec2(25, -70);
		actRight.blackList.emplace_back(ACT::FALLING);
		actRight.blackList.emplace_back(ACT::JUMPING);
		actRight.action = ACT::RIGHT;
		actCtl->AddModule("右移動", actRight);
	}
	{
		//落下
		actModule actFall;
		actFall.velocity = Vec2(5, -1);
		actFall.reverce  = false;
		actFall.keyCode  = EventKeyboard::KeyCode::KEY_NONE;
		actFall.animName = "player-run";
		actFall.sprite   = this;
		actFall.offset   = Vec2(-25, -(getContentSize().height / 2));
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
		actFalling.animName = "player-run";
		actFalling.sprite = this;
		actFalling.offset = Vec2(-25, -(getContentSize().height / 2));
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
		actJump.animName = "player-run";
		actJump.sprite = this;
		actJump.offset = Vec2(25, 120);
		actJump.blackList.emplace_back(ACT::FALL);
		actJump.blackList.emplace_back(ACT::FALLING);
		actJump.blackList.emplace_back(ACT::JUMPING);
		actJump.action = ACT::JUMP;
		actJump.jumpHeight = 15;
		actCtl->AddModule("ジャンプ", actJump);
	}
	{
		//ジャンプ中
		actModule actJumping;
		actJumping.velocity = Vec2(5, 0.5f);
		actJumping.reverce = true;
		actJumping.keyCode = EventKeyboard::KeyCode::KEY_SPACE;
		actJumping.animName = "player-run";
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
	{
		//攻撃
		actModule actAttack;
		actAttack.velocity = Vec2(5, 0);
		actAttack.reverce = true;
		actAttack.keyCode = EventKeyboard::KeyCode::KEY_ENTER;
		actAttack.animName = "player-jump";
		actAttack.sprite = this;
		actAttack.offset = Vec2(25, -70);
		actAttack.action = ACT::ATTACK;
		actAttack.blackList.emplace_back(ACT::FALLING);
		actAttack.blackList.emplace_back(ACT::JUMPING);
		actCtl->AddModule("攻撃", actAttack);
	}
}
