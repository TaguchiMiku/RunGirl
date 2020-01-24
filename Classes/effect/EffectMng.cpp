#include "EffectMng.h"

USING_NS_CC;
using namespace efk;

std::unique_ptr<EffectMng, EffectMng::EffectMngDeleter> EffectMng::s_instance(new EffectMng());

void EffectMng::Init(void)
{
	manager = EffectManager::create(Director::getInstance()->getVisibleSize());
}

void EffectMng::AddEffect(std::string name)
{
	if (mapEffect.find(name) == mapEffect.end())
	{
		mapEffect.emplace(name, Effect::create("effect/" + name + ".efk"));
		mapEffect[name]->retain();
	}
}

efk::Effect * EffectMng::GetEffect(std::string name)
{
	AddEffect(name);
	return mapEffect[name];
}

efk::EffectManager * EffectMng::GetEffectManager()
{
	return manager;
}

EffectEmitter* EffectMng::Play(std::string  name, Vec2 position, int scale, float speed, bool looping)
{
	//何回も生成されてしまう
	auto emitter = EffectEmitter::create(manager);
	emitter->setPosition(position);
	emitter->setScale(scale);
	emitter->setEffect(GetEffect(name));
	emitter->setSpeed(speed);
	emitter->setIsLooping(looping);
	emitter->setName(name);
	emitter->play();
	return emitter;
}

EffectMng::EffectMng()
{
}


EffectMng::~EffectMng()
{
	manager->release();
}
