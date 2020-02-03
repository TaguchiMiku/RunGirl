#include "cocos2d.h"
#include "Animation\AnimCtl.h"
#include <list>

struct actModule;
using functionModule = std::function<bool(cocos2d::Sprite&, actModule&)>;

enum class ACT{
	IDLE,
	LEFT,
	RIGHT,
	JUMP,
	JUMPING,
	FALL,
	FALLING,
	ATTACK,
	DIE
};

struct actModule
{
	cocos2d::Sprite* sprite;
	cocos2d::Vec2 velocity;					//ベクトル
	bool reverce;							//左右反転フラグ
	std::string animName;							//アニメーション種類
	cocos2d::EventKeyboard::KeyCode keyCode;//キーコード
	cocos2d::EventKeyboard::KeyCode nowKey; //キーコード
	cocos2d::EventKeyboard::KeyCode oldKey;	//キーコード
	functionModule runAction;				//関数ポインタを呼ぶ関数
	std::list<functionModule> act;			//チェック用関数ポインタのリスト
	std::list<ACT> whiteList;				//次の動きを実行していいリスト
	std::list<ACT> blackList;				//次の動きを実行できないリスト
	ACT action;								//現在のアクション情報
	ACT beforeAction;						//1つ前に実行されたアクション情報
	std::list<cocos2d::Vec2> offset;					//当たり判定用オフセット
	cocos2d::Action* actionData;
	float gravity;							//重力加速度
	float jumpHeight;						//ジャンプの高さ
};
