#pragma once
#include "cocos2d.h"

#if (_DEBUG && (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32))
#include <windows.h>
//引数の文字をコンソールに出力する
#define TRACE(fmt, ...) printf(fmt, __VA_ARGS__)//...が任意の連結した文字列(可変引数)、_がばらしてくれる。
//デバッグメッセージを表示するための定義
#define AST() {\
	CHAR ast_mes[256];\
	wsprintf(ast_mes, "%s %d行目\0", __FILE__, __LINE__);\
	MessageBox(0, ast_mes, "アサート表示", MB_OK);\
	}

class _DebugConOut
{
public:
	static _DebugConOut& GetInstance()
	{
		static _DebugConOut s_Instance;
		return s_Instance;
	}

private:
	_DebugConOut();
	~_DebugConOut();

	FILE* _debugFp = nullptr;
};
#else
#define TRACE(fmt, ...)
#define AST()
#endif

