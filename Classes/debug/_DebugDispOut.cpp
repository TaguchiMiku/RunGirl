#ifdef _DEBUG
#include "_DebugDispOut.h"
#include "_DebugConOut.h"

void _DebugDispOut::AddLayer(cocos2d::Node* nd)
{
	auto director = cocos2d::Director::getInstance();
	auto layer = (cocos2d::Layer*)director->getRunningScene()->getChildByName("DEBUG_LAYER");
	if (!layer->getChildByName(nd->getName()))
	{
		layer->addChild(nd);
	}
}

void _DebugDispOut::DrawRect(cocos2d::Vec2 pos, cocos2d::Vec2 size)
{
	auto rect = cocos2d::DrawNode::create();
	// drawRect(開始点の座標、終了点の座標, 色)
	rect->drawRect(cocos2d::Vec2(pos.x, pos.y), cocos2d::Vec2(pos.x - size.x, pos.y - size.y), cocos2d::Color4F(1, 1, 0, 1));
	rect->setName("DrawRect");
	AddLayer(rect);
}

_DebugDispOut::_DebugDispOut()
{
}

_DebugDispOut::~_DebugDispOut()
{
}
#endif
