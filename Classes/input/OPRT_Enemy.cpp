#include "OPRT_Enemy.h"

USING_NS_CC;

OPRT_Enemy::OPRT_Enemy()
{
}

OPRT_Enemy::~OPRT_Enemy()
{
}

void OPRT_Enemy::Update()
{
	data.key.second = data.key.first;
	data.key.first = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
}
