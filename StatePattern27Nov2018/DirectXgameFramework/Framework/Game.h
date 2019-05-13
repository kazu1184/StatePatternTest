/*
@brief		ゲーム
@file		Game.h
@date		2018/11/27
@author		Shozo Tanaka
*/

#pragma once
#ifndef GAME_DEFINED
#define GAME_DEFINED

// Use the C++ standard templated min/max
#define NOMINMAX

#include <windows.h>
#include <iostream>
#include <string>
#include <iomanip>

#include <d3d11.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <Effects.h>
#include <Model.h>
#include <Keyboard.h>
#include <GeometricPrimitive.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <algorithm>

#include "..\\Framework\\StepTimer.h"
#include "..\\Framework\\dx.h"
#include "..\\Framework\\Window.h"
#include "..\\Framework\\Graphics.h"

#include "..\\Game\\Scene.h"
#include "..\\Game\\TitleScene.h"


using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace DX;
using namespace std;

class Window;

// ゲームを実装する 
class Game {
public:
	// コンストラクタ (Constructor)
    Game(int width, int height);
    // ゲームに必要なオブジェクトを初期する (Initialize game object)
    void Initialize();
    // 基本ゲームループを実行する (Run basic game loop)
	MSG Run();
	// 終了処理をおこなう (Finalize game)
	void Finalize();

    // メッセージ (Messages)
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // プロパティ (Properties)
    void GetDefaultSize(int& width, int& height) const;

private:
	// ゲームを更新する (Update game)
    void Update(const StepTimer& timer);
    // シーンを描画する (Render scene)
	void Render();
	// バックバッファをクリアする (Clear back buffer)
    void Clear();
	// バックバッファをスクリーンに送る
    void Present();
	// FPSを描画する (Draw FPS)
	void DrawFPS();

private:
	// インスタンスハンドル Instance handle
	HINSTANCE hInstance;
	// 実行時のウィンドウの表示方法 Initial state of main window 
	int nCmdShow;
    // ウィンドウハンドル Windows handle
    HWND hWnd;
	// ウィンドウ幅 Window width
    int width;
	// ウィンドウ高 Window height
    int height;

	// ウィンドウ Window
	unique_ptr<Window> window;
	// DirectXグラフィックス DirectX Graphics
	unique_ptr<Graphics> graphics;
	// 機能レベル Feature level
    D3D_FEATURE_LEVEL featureLevel;
    // ループタイマー Loop timer
    StepTimer timer;

	// スプライトバッチ SpriteBatch
	unique_ptr<SpriteBatch>	spriteBatch;
	// フォント Font
	unique_ptr<SpriteFont> font;

	// エフェクトファクトリインターフェース IEffectFactory
	unique_ptr<IEffectFactory> fxFactory;
	// コモンステート CommonStates
	unique_ptr<CommonStates> commonStates;

	// 現在のシーン current scene
	Scene* currentScene;
};

#endif	// GAME
