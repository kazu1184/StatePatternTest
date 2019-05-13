/*
@brief		WinMain
@file		Main.cpp
@date		2018/11/25
@author		Shozo Tanaka
*/

#include "..\\Framework\\Game.h"

using namespace DirectX;
using namespace std;


// エントリポイント Entry point
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (!XMVerifyCPUSupport())
        return 1;
	// COMライブラリを初期化する
    if (FAILED(CoInitializeEx(nullptr, COINITBASE_MULTITHREADED)))
        return 1;

	// Gameオブジェクトを生成する
	Game game(WINDOW_WIDTH, WINDOW_HEIGHT);
	// ゲームを実行する
	MSG msg = game.Run();

	// COMライブラリの終了処理する
    CoUninitialize();
    return (int) msg.wParam;
}
