#include "OPRT_Key.h"
#include "debug/_DebugConOut.h"

USING_NS_CC;

OPRT_Key::OPRT_Key()
{
	data.key.first = EventKeyboard::KeyCode::KEY_NONE;
	data.key.second = EventKeyboard::KeyCode::KEY_NONE;
	data.id.first = EventKeyboard::KeyCode::KEY_NONE;
	data.id.second = EventKeyboard::KeyCode::KEY_NONE;
	key = EventKeyboard::KeyCode::KEY_NONE;
	pushFlag = false;
}

OPRT_Key::OPRT_Key(Node * nd)
{
	data.key.first = EventKeyboard::KeyCode::KEY_NONE;
	data.key.second = EventKeyboard::KeyCode::KEY_NONE;
	data.id.first = EventKeyboard::KeyCode::KEY_NONE;
	data.id.second = EventKeyboard::KeyCode::KEY_NONE;
	key = EventKeyboard::KeyCode::KEY_NONE;

	listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
		if (data.id.first != EventKeyboard::KeyCode::KEY_NONE)
		{
			data.id.second = keyCode;
		}
		if (data.id.second == EventKeyboard::KeyCode::KEY_NONE)
		{
			data.id.first = keyCode;
		}
		key = keyCode;
		pushFlag = true;
		clickFlag = false;
	};

	listener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event) {
		if (data.id.first == keyCode)
		{
			data.id.first = EventKeyboard::KeyCode::KEY_NONE;
		}
		if (data.id.second == keyCode)
		{
			data.id.second = EventKeyboard::KeyCode::KEY_NONE;
		}
		key = keyCode;
		pushFlag = false;
	};

	nd->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, nd);

	listener_mouse = EventListenerTouchOneByOne::create();
	listener_mouse->onTouchBegan = [this](Touch* touch, Event* event) {
		key = EventKeyboard::KeyCode::KEY_ENTER;
		clickFlag = true;
		return true;
	};
	listener_mouse->onTouchEnded = [this](Touch* touch, Event* event) {
		key = EventKeyboard::KeyCode::KEY_NONE;
		clickFlag = false;
	};
	nd->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener_mouse, nd);
}


OPRT_Key::~OPRT_Key()
{
}

void OPRT_Key::Update()
{
	//TRACE("%f\n", key);
	data.key.second = data.key.first;
	data.key.first = key;
	if (!pushFlag/* && !clickFlag*/)
	{
		key = EventKeyboard::KeyCode::KEY_NONE;
	}
}

