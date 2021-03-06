#include "OPRT_Touch.h"
#include "base/CCDirector.h"
#include "effect/EffectMng.h"

//#include "sound/SoundMng.h"

USING_NS_CC;

OPRT_Touch::OPRT_Touch()
{
	touchPos = { 0.0f, 0.0f };
	windowSize = Director::getInstance()->getVisibleSize();

	data.key.first = EventKeyboard::KeyCode::KEY_NONE;
	data.key.second = EventKeyboard::KeyCode::KEY_NONE;
	data.id.first = EventKeyboard::KeyCode::KEY_NONE;
	data.id.second = EventKeyboard::KeyCode::KEY_NONE;
	key = EventKeyboard::KeyCode::KEY_NONE;
	pushFlag = false;
}

OPRT_Touch::OPRT_Touch(Node * nd)
{
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		touchPos = touch->getLocation();
		lpEffectMng.Play("starTap", touchPos, 1.0f, 2, false);
		if (touchPos.x <= Director::getInstance()->getVisibleSize().width / 2.0f)
		{
			key = EventKeyboard::KeyCode::KEY_A;
		}
		else
		{
			key = EventKeyboard::KeyCode::KEY_S;
		}
		pushFlag = true;
		return true;
	};
	listener->onTouchMoved = [this](Touch* touch, Event* event) {
	};
	listener->onTouchEnded = [this](Touch* touch, Event* event) {
		touchPos = touch->getLocation();
		pushFlag = false;
	};

	nd->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, nd);
}


OPRT_Touch::~OPRT_Touch()
{
}

void OPRT_Touch::Update()
{
	data.key.second = data.key.first;
	data.key.first = key;
	if (!pushFlag)
	{
		key = EventKeyboard::KeyCode::KEY_NONE;
	}
}

