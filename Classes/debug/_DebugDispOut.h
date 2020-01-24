#pragma once
#include <cocos2d.h>

#ifdef _DEBUG
#define _dbDrawRect(fmt, ...) _DebugDispOut::GetInstance().DrawRect(fmt, __VA_ARGS__)

class _DebugDispOut
{
public:
	static _DebugDispOut& GetInstance()
	{
		static _DebugDispOut s_Instance;
		return s_Instance;
	}
	void AddLayer(cocos2d::Node* nd);
	void DrawRect(cocos2d::Vec2 pos, cocos2d::Vec2 size);


private:
	_DebugDispOut();
	~_DebugDispOut();

	cocos2d::Sprite* square;
};
#else
//Release
#define _dbDrawRect(fmt, ...)

#endif //_DEBUG

