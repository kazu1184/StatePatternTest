/*
@brief		スタンディング
@file		Standing.h
@date		2018/11/25
@author		Shozo Tanaka
*/

#pragma once
#ifndef STANDING_DEFINED
#define STANDING_DEFINED

#include <windows.h>
#include <wrl/client.h>
#include <d3d11.h>
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

class IState;
class Player;

// Standingクラスを宣言する (Declare Standing class)
class Standing : public IState {
public:
	// Standingクラスのインスタンスを取得する (Get instance of Standing class)
	static IState* GetInstance();
	// Standingオブジェクトを初期化する (Initialize Standing object)
	void Initialize(Player* player) override;
	// Standingオブジェクトを実行する (Execute Standing object)
	void Execute(const DX::StepTimer& timer) override;
	// Standingオブジェクトを描画する (Render Standing object)
	void Render(SpriteBatch* spriteBatch) override;
	// Standingオブジェクトを破棄する (Delete Standing object)
	static void Dispose();

private:
	// コンストラクタ
	Standing();
	// Stangingオブジェクトへのポインタ
	static IState* state;
	// Playerオブジェクトへのポインタ
	Player* player;
	// テクスチャオブジェクトへのポインタ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	// テクスチャ幅
	int width;
	// テクスチャ高
	int height;
};

#endif // STANDING_DEFINED