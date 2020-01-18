#pragma once
#include "cocos2d.h"
#include <memory>
#include <map>
#include "effect/Players/Cocos2d-x_v3/Effekseer.h"

#define lpEffectMng EffectMng::GetInstance()//EffectMng���O������Q�Ƃ���ۂɒZ���R�[�h�ŏ������߂̒�`
class EffectMng
{
public:
	static EffectMng& GetInstance()	//�O������public�Ȋ֐����Ăяo���p�̃Q�b�^�[
	{
		return *s_instance;			//���g�̃N���X�̃|�C���^�[��Ԃ�
	}
	void Init(cocos2d::Layer& layer, efk::EffectManager* manager);
	efk::EffectEmitter* Play(std::string name, cocos2d::Vec2 position, int scale, float speed, bool looping);
	efk::EffectEmitter* PlayAgain(std::string name, cocos2d::Vec2 position, int scale, float speed, bool looping);
	efk::Effect * GetEffect(efk::EffectEmitter* emitter);

private:
	struct EffectMngDeleter	//unique_ptr�p�̎���f�X�g���N�^�[
	{
		void operator()(EffectMng* efkMng) const
		{
			//�Ă΂ꂽ��EffectMng�V�[����j������
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

