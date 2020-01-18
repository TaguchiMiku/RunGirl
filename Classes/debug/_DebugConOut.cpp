#ifdef _DEBUG
#include "_DebugConOut.h"

_DebugConOut::_DebugConOut()
{
	HWND hWnd = GetForegroundWindow();				//前にあるwindowのハンドルを取得
	AllocConsole();									//コンソール表示
	SetForegroundWindow(hWnd);						//最初に設定したwindowを前にする
	freopen_s(&_debugFp, "CONOUT$", "w", stdout);	//文字列の出力
	freopen_s(&_debugFp, "CONIN$", "r", stdin);		//文字列の入力
}


_DebugConOut::~_DebugConOut()
{
	FreeConsole();	//コンソール削除
}

#endif
