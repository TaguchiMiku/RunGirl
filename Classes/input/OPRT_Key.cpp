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
}


OPRT_Key::~OPRT_Key()
{
}

void OPRT_Key::Update()
{
	data.key.second = data.key.first;
	data.key.first = key;
	//‰Ÿ‚µ‚Ä‚éŠÔ
	if (pushFlag && (data.key.second == data.key.first))
	{
		key = EventKeyboard::KeyCode::KEY_NONE;
	}
	if (!pushFlag)
	{
		key = EventKeyboard::KeyCode::KEY_NONE;
	}
}

