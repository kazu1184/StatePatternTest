/*
@brief		ジャンピング
@file		Jumping.h
@date		2018/11/25
@author		Shozo Tanaka
*/

#pragma once
#ifndef JUMPING_DEFINED
#define JUMPING_DEFINED

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
#include "..\Framework\\Input.h"
#include "..\\Game\\Player.h"
#include "..\Game\\IState.h"

class Player;
class IState;

// Jumpingクラスを宣言する
class Jumping : public IState 
{
public:
	// Jumpingクラスのインスタンスを取得する
	static IState* GetInstance();
	// Jumpingオブジェクトを初期化する
	void Initialize(Player* player) override;
	// Jumpingオブジェクを実行する
	void Execute(const DX::StepTimer& timer) override;
	// Jumpingオブジェクトを描画する
	void Render(SpriteBatch* spriteBatch) override;
	// Jumpingオブジェクトを破棄する
	static void Dispose();
	
private:
	// コンストラクタ
	Jumping();
	// Jumpingオブジェクトへのポインタ
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

#endif // JUMPING