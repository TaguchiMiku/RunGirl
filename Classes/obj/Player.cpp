#include "Player.h"
#include "effect/EffectMng.h"
#include "../ResultScene.h"
#include "ui/CountDown.h"
#include "Score.h"
#include "obj/DashFx.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "input/OPRT_Key.h"
#include "sound/SoundMng.h"
#include "../debug/_DebugConOut.h"
#include "../debug/_DebugDispOutCC.h"
#else
#include "input/OPRT_Touch.h"
#endif

USING_NS_CC;

#pragma execution_charactor_set("utf-8");

Player::Player()
{
	Init();
}

Player::~Player()
{
}

Unit * Player::createUnit()
{
	return Player::create();
}

void Player::Init()
{
	// 画面サイズと原点を取得
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	setPosition(Vec2(visibleSize.width / 2.0f + origin.x, 400.0f + origin.y));

	// アニメーションの初期化//シーンの先頭で読み込む
	lpAnimCtl.AddAnimation("player", "idle", 0.05f);
	lpAnimCtl.AddAnimation("player", "walk", 0.1f);
	lpAnimCtl.AddAnimation("player", "run-slow", 0.07f);
	lpAnimCtl.AddAnimation("player", "run", 0.05f);
	lpAnimCtl.AddAnimation("player", "run2", 0.03f);
	lpAnimCtl.AddAnimation("player", "jump", 0.05f);
	lpAnimCtl.AddAnimation("player", "attack", 0.1f);
	lpAnimCtl.AddAnimation("player", "attack2", 0.1f);

	lpAnimCtl.RunAnimation(this, "player-idle", -1, 0);

	// アクションデータを設定(追加)する
	velocityX = 5.0f;
	AddActData();
	jumpSpeed = 0.0f;
	nowAction = ACT::IDLE;
	accelFlag = false;
	attackFlag = false;
	timeUpFlag = false;
	slowlyFlag = false;
	time = 0.0f;
	dashFxTime = 0.0f;
	this->setName("Player");
// プラットフォーム別に入力クラス（操作の仕方）を切り替える
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	oprt_state.reset(new OPRT_Key(this));
#else
	oprt_state.reset(new OPRT_Touch(this));
#endif
	scheduleUpdate();
}

//毎フレーム更新関数
void Player::Update(float delta)
{
	// 制限時間になったら止める
	if (timeUpFlag)
	{
		return;
	}

	//TRACE("%f\n", getPositionX());

	// 加速する時間
	if (accelFlag)
	{
		auto score = static_cast<Score*>(Director::getInstance()->getRunningScene()->getChildByName("Score"));
		score->AddScore(50);
		time += delta;
		velocityX = 10.0f;
		if (time >= 3.0f)
		{
			time = 0.0f;
			velocityX = 5.0f;
			accelFlag = false;
		}
	}
	if (slowlyFlag)
	{
		time += delta;
		velocityX = 2.0f;
		if (time >= 3.0f)
		{
			time = 0.0f;
			velocityX = 5.0f;
			slowlyFlag = false;
		}
	}

	// ダッシュエフェクト生成
	if (nowAction == ACT::RIGHT || nowAction == ACT::ATTACK)
	{
		auto dashFxSet = [](std::string animName, Vec2 position, Vec2 scale)
		{
			auto dash = DashFx::createDash();
			dash->SetAddAnim(animName);
			dash->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
			dash->setPosition(position);
			dash->setScale(scale.x, scale.y);
			auto layer = static_cast<Layer*>(Director::getInstance()->getRunningScene()->getChildByName("plLayer"));
			layer->addChild(dash, 2);
		};

		dashFxTime += delta;
		if (attackFlag)
		{
			if (dashFxTime > 0.07f)
			{
				dashFxTime = 0.0f;
				dashFxSet("dash-a", Vec2(getPosition().x - 30.0f, getPosition().y - getContentSize().height / 2.0f - 2), Vec2(2.0f, 2.0f));
			}
		}
		else if (accelFlag)
		{
			if (dashFxTime > 0.1f)
			{
				dashFxTime = 0.0f;
				dashFxSet("dash-a", Vec2(getPosition().x - 20.0f, getPosition().y - getContentSize().height / 2.0f), Vec2(1.0f, 1.0f));
			}
		}
		else
		{
			if (dashFxTime > 0.25f)
			{
				dashFxTime = 0.0f;
				dashFxSet("dash-b", Vec2(getPosition().x - 20.0f, getPosition().y - getContentSize().height / 2.0f - 3.0f), Vec2(1.0f, 1.0f));
			}
		}
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	//DEBUG_DrawRect("plBox", getPosition(), Vec2(-16.0f, 22.0f), Vec2(17.0f, -27.0f), Color4F(1.0f, 1.0f, 1.0f, 1.0f));
#endif
	// input処理とaction処理
	oprt_state->Update();
	data = oprt_state->GetData();
	actCtl->MoveModule(data, delta);
	// 追従カメラ設定
	cameraCtl->FollowPlayer(Vec3(this->getPosition().x, this->getPosition().y, 500.0f));
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
	time = 0.0f;
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

void Player::SetSlowlyFlag(bool flag)
{
	slowlyFlag = flag;
}

bool Player::GetSlowlyFlag()
{
	return slowlyFlag;
}

float Player::GetVelocityX()
{
	return velocityX;
}

void Player::AddActData()
{
	cameraCtl.reset(new CameraCtl());
	actCtl.reset(new ActionCtl());

	{
		//右移動
		actModule actRight;
		actRight.velocity = Vec2(velocityX, 0.0f);
		actRight.reverce = false;
		actRight.keyCode = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
		actRight.animName = "player-run";
		actRight.sprite = this;
		actRight.offset.emplace_back(Vec2(17.0f, 28.0f));
		actRight.offset.emplace_back(Vec2(17.0f, -27.0f));
		actRight.action = ACT::RIGHT;
		actCtl->AddModule("右移動", actRight);
	}
	{
		//落下
		actModule actFall;
		actFall.velocity = Vec2(0.0f, -1.0f);
		actFall.reverce  = false;
		actFall.keyCode  = EventKeyboard::KeyCode::KEY_NONE;
		actFall.animName = "player-jump";
		actFall.sprite   = this;
		actFall.offset.emplace_back(Vec2(-16.0f, -27.0f));
		actFall.offset.emplace_back(Vec2(17.0f, -27.0f));
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
		actFalling.velocity = Vec2(0.0f, -1.0f);
		actFalling.reverce = false;
		actFalling.keyCode = EventKeyboard::KeyCode::KEY_NONE;
		actFalling.animName = "player-jump";
		actFalling.sprite = this;
		actFalling.offset.emplace_back(Vec2(-16.0f, -27.0f));
		actFalling.offset.emplace_back(Vec2(17.0f, -27.0f));
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
		actJump.animName = "player-jump";
		actJump.sprite = this;
		actJump.offset.emplace_back(Vec2(-16.0f, 28.0f));
		actJump.offset.emplace_back(Vec2(17.0f, 28.0f));
		actJump.blackList.emplace_back(ACT::FALL);
		actJump.blackList.emplace_back(ACT::FALLING);
		actJump.blackList.emplace_back(ACT::JUMPING);
		actJump.action = ACT::JUMP;
		actJump.jumpHeight = 15.0f;
		actCtl->AddModule("ジャンプ", actJump);
	}
	{
		//ジャンプ中
		actModule actJumping;
		actJumping.velocity = Vec2(0.0f, 0.5f);
		actJumping.reverce = true;
		actJumping.keyCode = EventKeyboard::KeyCode::KEY_A;
		actJumping.animName = "player-jump";
		actJumping.sprite = this;
		actJumping.offset.emplace_back(Vec2(-16.0f, 28.0f));
		actJumping.offset.emplace_back(Vec2(17.0f, 28.0f));
		actJumping.offset.emplace_back(Vec2(17.0f, -27.0f));
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
		actAttack.animName = "player-attack2";
		actAttack.sprite = this;
		actAttack.offset.emplace_back(Vec2(17.0f, 28.0f));
		actAttack.offset.emplace_back(Vec2(17.0f, -27.0f));
		actAttack.action = ACT::ATTACK;
		actAttack.blackList.emplace_back(ACT::FALL);
		actAttack.blackList.emplace_back(ACT::FALLING);
		actAttack.blackList.emplace_back(ACT::JUMPING);
		actAttack.blackList.emplace_back(ACT::JUMP);
		actAttack.actionData = nullptr;
		actCtl->AddModule("攻撃", actAttack);
	}
}
