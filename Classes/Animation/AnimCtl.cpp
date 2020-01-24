#include "AnimCtl.h"

std::unique_ptr<AnimCtl, AnimCtl::AnimCtlDeleter> AnimCtl::s_instance(new AnimCtl());

USING_NS_CC;

std::string AnimCtl::AddAnimation(std::string unit, std::string action, float animSpeed)
{
	auto cache = SpriteFrameCache::getInstance();
	auto actName = unit + "-" + action;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/Sprites/" + unit + "/" + actName + "/sprites.plist");
	animation = Animation::create();

	for (int j = 1; j < 100; j++)
	{
		auto spFrame = cache->getSpriteFrameByName(actName + "-" + std::to_string(j) + ".png");
		if (spFrame != nullptr)
		{
			animation->addSpriteFrame(spFrame);
		}
		else
		{
			break;
		}
	}
	animation->setDelayPerUnit(animSpeed);
	animation->setRestoreOriginalFrame(true);
	AnimationCache::getInstance()->addAnimation(animation, actName);
	return actName;
}

Action * AnimCtl::RunAnimation(Node * sprite, std::string action, int repeatCnt)
{
	animation = AnimationCache::getInstance()->getAnimation(action);
	if (animation != nullptr)
	{
		if (repeatCnt >= 0)
		{
			auto action = Repeat::create(Animate::create(animation), repeatCnt);
			//retain()���Ȃ���isDone()���g�p�����ۂɎ���������ꂽ��Ȃ̂Ń��������[�N���N����B
			//�����h�����߂ɁA�����ŃJ�E���g���v���X���Ă����K�v������B
			action->retain();
			return sprite->runAction(action);
		}
		else
		{
			return sprite->runAction(RepeatForever::create(Animate::create(animation)));
		}
	}
	return nullptr;
}

AnimCtl::AnimCtl()
{
}

AnimCtl::~AnimCtl()
{
}