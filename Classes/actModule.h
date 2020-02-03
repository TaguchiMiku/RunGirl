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
	cocos2d::Vec2 velocity;					//�x�N�g��
	bool reverce;							//���E���]�t���O
	std::string animName;							//�A�j���[�V�������
	cocos2d::EventKeyboard::KeyCode keyCode;//�L�[�R�[�h
	cocos2d::EventKeyboard::KeyCode nowKey; //�L�[�R�[�h
	cocos2d::EventKeyboard::KeyCode oldKey;	//�L�[�R�[�h
	functionModule runAction;				//�֐��|�C���^���ĂԊ֐�
	std::list<functionModule> act;			//�`�F�b�N�p�֐��|�C���^�̃��X�g
	std::list<ACT> whiteList;				//���̓��������s���Ă������X�g
	std::list<ACT> blackList;				//���̓��������s�ł��Ȃ����X�g
	ACT action;								//���݂̃A�N�V�������
	ACT beforeAction;						//1�O�Ɏ��s���ꂽ�A�N�V�������
	std::list<cocos2d::Vec2> offset;					//�����蔻��p�I�t�Z�b�g
	cocos2d::Action* actionData;
	float gravity;							//�d�͉����x
	float jumpHeight;						//�W�����v�̍���
};
