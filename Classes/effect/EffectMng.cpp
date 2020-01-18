#include "EffectMng.h"

USING_NS_CC;
using namespace efk;

std::unique_ptr<EffectMng, EffectMng::EffectMngDeleter> EffectMng::s_instance(new EffectMng());

void EffectMng::Init(cocos2d::Layer & layer, efk::EffectManager * manager)
{
	this->manager = manager;
	this->layer = &layer;
}

EffectEmitter* EffectMng::Play(std::string  name, Vec2 position, int scale, float speed, bool looping)
{
	//何回も生成されてしまう
	auto effect = Effect::create("effect/" + name + ".efk");
	auto emitter = EffectEmitter::create(manager);
	emitter->setPosition(position);
	emitter->setScale(scale);
	emitter->setEffect(effect);
	emitter->setSpeed(speed);
	emitter->setIsLooping(looping);
	layer->addChild(emitter, 0);
	emitter->setName(name);
	emitter->play();
	return emitter;
}

efk::EffectEmitter * EffectMng::PlayAgain(std::string name, cocos2d::Vec2 position, int scale, float speed, bool looping)
{

	return nullptr;
}

Effect * EffectMng::GetEffect(EffectEmitter* emitter)
{
	return emitter->getEffect();
}

EffectMng::EffectMng()
{
}


EffectMng::~EffectMng()
{
}
