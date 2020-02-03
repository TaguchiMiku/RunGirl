#pragma once
#include "cocos2d.h"
#include "../2d/CCNode.h"
#include <array>
#include <memory>
#include <utility>
#include <string>

//アニメーションの種類
enum class ANIM_ST {
//複数コマアニメーション	
	HUNT,		//攻撃を食らった
	IDLE,		//待ち状態
	JUMP,		//ジャンプ
	RUN,		//走る
	RUN_SHOT,	//走りながら撃つ
	STAND,		//銃を構えて立つ
//1コマアニメーション
	SHOOT_UP,	//上向きに撃つ
	CLING,		//登る
	DUCK,		//しゃがみ構える
	MAX
};

#define lpAnimCtl AnimCtl::GetInstance()//AnimCtlを外部から参照する際に短いコードで書くための定義
using AnimInfo = std::array<cocos2d::Animation*, static_cast<int>(ANIM_ST::MAX)>;//アニメーション情報、アニメーションの種類

class AnimCtl
{
public:
	static AnimCtl& GetInstance()	//外部からpublicな関数を呼び出す用のゲッター
	{
		return *s_instance;			//自身のクラスのポインターを返す
	}
	std::string AddAnimation(std::string unit, std::string action, float animSpeed);
	cocos2d::Action* RunAnimation(cocos2d::Node* sprite, std::string action, int repeatCnt, int tag);

private:
	struct AnimCtlDeleter	//unique_ptr用の自作デストラクター
	{
		void operator()(AnimCtl* animCtl) const
		{
			//呼ばれたらAnimCtlシーンを破棄する
			delete animCtl;
		}
	};
	AnimCtl();
	~AnimCtl();
	static std::unique_ptr<AnimCtl, AnimCtlDeleter> s_instance;
	cocos2d::Animation* animation;
};