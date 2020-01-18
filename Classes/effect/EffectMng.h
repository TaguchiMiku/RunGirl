#pragma once
#include "cocos2d.h"
#include <memory>
#include <map>
#include "effect/Players/Cocos2d-x_v3/Effekseer.h"

#define lpEffectMng EffectMng::GetInstance()//EffectMngを外部から参照する際に短いコードで書くための定義
class EffectMng
{
public:
	static EffectMng& GetInstance()	//外部からpublicな関数を呼び出す用のゲッター
	{
		return *s_instance;			//自身のクラスのポインターを返す
	}
	void Init(cocos2d::Layer& layer, efk::EffectManager* manager);
	efk::EffectEmitter* Play(std::string name, cocos2d::Vec2 position, int scale, float speed, bool looping);
	efk::EffectEmitter* PlayAgain(std::string name, cocos2d::Vec2 position, int scale, float speed, bool looping);
	efk::Effect * GetEffect(efk::EffectEmitter* emitter);

private:
	struct EffectMngDeleter	//unique_ptr用の自作デストラクター
	{
		void operator()(EffectMng* efkMng) const
		{
			//呼ばれたらEffectMngシーンを破棄する
			delete efkMng;
		}
	};
	EffectMng();
	~EffectMng();
	static std::unique_ptr<EffectMng, EffectMngDeleter> s_instance;
	std::map<std::string, efk::EffectEmitter*> mapEffect;
	efk::EffectManager* manager;
	cocos2d::Layer* layer;
};

