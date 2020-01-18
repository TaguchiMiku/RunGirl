#include "OPRT_Touch.h"
#include "base/CCDirector.h"
//#include "sound/SoundMng.h"

USING_NS_CC;

OPRT_Touch::OPRT_Touch()
{
	touchPos = { 0, 0 };
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
		//lpSoundMng.OnceSoundPlay("Resources/sound/jump2.ckb");
		touchPos = touch->getLocation();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		key = EventKeyboard::KeyCode::KEY_ENTER;
#else
		key = EventKeyboard::KeyCode::KEY_SPACE;
#endif
		pushFlag = true;
		return true;
	};
	listener->onTouchMoved = [this](Touch* touch, Event* event) {
		/*if ((touch->getLocation().x - touchPos.x) > 10 && (touch->getLocation().y - touchPos.y) > 10)
		{
			key = EventKeyboard::KeyCode::KEY_ENTER;
		}*/
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

