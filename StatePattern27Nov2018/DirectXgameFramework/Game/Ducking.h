/*
@brief		屈む
@file		Ducking.h
@date		2018/11/25
@author		Shozo Tanaka
*/

#pragma once
#ifndef DUCKING_DEFINED
#define DUCKING_DEFINED

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


class Player;
class IState;

// Duckingクラスを宣言する(Declare Ducking class)
class Ducking : public IState {
public:
	// Duckingクラスのインスタンスを取得する (Get instance of Ducking class
	static IState* GetInstance();
	// Duckingオブジェクトを初期化する (Initialize Ducking object)
	void Initialize(Player* player) override;
	// Duckingオブジェクトを実行する (Execute Ducking object)
	void Execute(const DX::StepTimer& timer) override;
	// Duckingオブジェクトを描画する (Render Ducking object)
	void Render(SpriteBatch* spriteBatch) override;
	// Duckingオブジェクトを破棄する (Delete Ducking object)
	static void Dispose();

private:
	// コンストラクタ
	Ducking();
	// Duckingオブジェクトへのポインタ
	static IState* state;
	// Playerオブジェクトへのポインタ
	Player* player;
	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	// テクスチャ幅
	int width;
	// テクスチャ高
	int height;
};

#endif // DUCKING_DEFINED