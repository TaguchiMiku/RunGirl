#pragma once
#include "cocos2d.h"
#include "../2d/CCNode.h"
#include <array>
#include <memory>
#include <utility>
#include <string>

//�A�j���[�V�����̎��
enum class ANIM_ST {
//�����R�}�A�j���[�V����	
	HUNT,		//�U����H�����
	IDLE,		//�҂����
	JUMP,		//�W�����v
	RUN,		//����
	RUN_SHOT,	//����Ȃ��猂��
	STAND,		//�e���\���ė���
//1�R�}�A�j���[�V����
	SHOOT_UP,	//������Ɍ���
	CLING,		//�o��
	DUCK,		//���Ⴊ�ݍ\����
	MAX
};

#define lpAnimCtl AnimCtl::GetInstance()//AnimCtl���O������Q�Ƃ���ۂɒZ���R�[�h�ŏ������߂̒�`
using AnimInfo = std::array<cocos2d::Animation*, static_cast<int>(ANIM_ST::MAX)>;//�A�j���[�V�������A�A�j���[�V�����̎��

class AnimCtl
{
public:
	static AnimCtl& GetInstance()	//�O������public�Ȋ֐����Ăяo���p�̃Q�b�^�[
	{
		return *s_instance;			//���g�̃N���X�̃|�C���^�[��Ԃ�
	}
	std::string AddAnimation(std::string unit, std::string action, float animSpeed);
	cocos2d::Action* RunAnimation(cocos2d::Node* sprite, std::string action, int repeatCnt, int tag);

private:
	struct AnimCtlDeleter	//unique_ptr�p�̎���f�X�g���N�^�[
	{
		void operator()(AnimCtl* animCtl) const
		{
			//�Ă΂ꂽ��AnimCtl�V�[����j������
			delete animCtl;
		}
	};
	AnimCtl();
	~AnimCtl();
	static std::unique_ptr<AnimCtl, AnimCtlDeleter> s_instance;
	cocos2d::Animation* animation;
};