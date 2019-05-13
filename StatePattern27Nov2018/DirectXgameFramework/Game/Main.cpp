/*
@brief		WinMain
@file		Main.cpp
@date		2018/11/25
@author		Shozo Tanaka
*/

#include "..\\Framework\\Game.h"

using namespace DirectX;
using namespace std;


// �G���g���|�C���g Entry point
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (!XMVerifyCPUSupport())
        return 1;
	// COM���C�u����������������
    if (FAILED(CoInitializeEx(nullptr, COINITBASE_MULTITHREADED)))
        return 1;

	// Game�I�u�W�F�N�g�𐶐�����
	Game game(WINDOW_WIDTH, WINDOW_HEIGHT);
	// �Q�[�������s����
	MSG msg = game.Run();

	// COM���C�u�����̏I����������
    CoUninitialize();
    return (int) msg.wParam;
}
