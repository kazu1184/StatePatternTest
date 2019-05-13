/*
@brief		ランニング
@file		Running.h
@date		2018/11/25
@author		Shozo Tanaka
*/

#pragma once
#ifndef RUNNING_DEFINED
#define RUNNING_DEFINED

#include <windows.h>
#include <wrl/client.h>
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <DirectXColors.h>
#include <WICTextureLoader.h>
#include <algorithm>
#include <Memory>

#include "..\\Framework\\Graphics.h"
#include "..\\Framework\\Input.h"
#include "..\\Game\\Player.h"
#include "..\\Game\\IState.h"
#include "..\\Game\\AnimatedTexture.h"

class IState;
class Player;

// Runningクラスを宣言する (Declare Standing class)
class Running : public IState {
public:
	// Runningクラスのインスタンスを取得する (Get instance of Running class)
	static IState* GetInstance();
	// Runningオブジェクトを初期化する (Initialize Running object)
	void Initialize(Player* player) override;
	// Runningオブジェクトを実行する (Execute Running object)
	void Execute(const DX::StepTimer& timer) override;
	// Runningオブジェクトを描画する (Render Running object)
	void Render(SpriteBatch* spriteBatch) override;
	// Runningオブジェクトを破棄する (Delete Running object)
	static void Dispose();
	// デストラクタ (Destructor)
	~Running();

private:
	// コンストラクタ
	Running();
	// Runningオブジェクトへのポインタ
	static IState* state;
	// Playerオブジェクトへのポインタ
	Player* player;
	// 描画しているテクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	// AnimationTexureオブジェクトへのポインタ
	AnimatedTexture* animatedTexture;
	// テクスチャ幅
	int width;
	// テクスチャ高
	int height;
};

#endif // RUNNING_DEFINED