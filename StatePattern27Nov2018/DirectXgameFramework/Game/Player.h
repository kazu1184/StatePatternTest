/*
@brief		プレイヤー
@file		Player.h
@date		2018/11/27
@author		Shozo Tanaka
*/

#pragma once
#ifndef PLAYER_DEFINED
#define PLAYER_DEFINED

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
#include <Keyboard.h>

#include "..\\Framework\\StepTimer.h"
#include "..\\Framework\\Graphics.h"
#include "..\\Framework\\Input.h"

#include "..\\Game\\Constant.h"
#include "..\\Game\\IState.h"
#include "..\\Game\\Standing.h"
#include "..\\Game\\Jumping.h"
#include "..\\Game\\Ducking.h"
#include "..\\Game\\Running.h"
#include "..\\Game\\AnimatedTexture.h"

// Playerクラスを宣言する (Declare Player class)
class Player {
public:
	// 向きを取得する
	bool Forward() { return this->forward; }
	// 向きを設定する
	void Forward(bool forward) { this->forward = forward; }
	// x座標を取得する
	float X() { return this->x; }
	// x座標を設定する
	void  X(float x) { this->x = x; }
	// y座標を取得する
	float Y() { return this->y; }
	// y座標を設定する
	void  Y(float y) { this->y = y; }

	// 速度(vx)を取得する
	float VX() { return this->vx; }
	// 速度(vy)を設定する
	void  VX(float vx) { this->vx = vx; }
	// 速度(vx)を取得する
	float VY() { return this->vy; }
	// 速度(vy)を設定する
	void  VY(float vy) { this->vy = vy; }

	// 加速度(ax)を取得する
	float AX() { return this->ax; }
	// 加速度(ax)を設定する
	void AX(float ax) { this->ax = ax; }
	// 加速度(ay)を取得する
	float AY() { return this->ay; }
	// 加速度(ay)を設定する
	void AY(float ay) { this->ay = ay; }

	// コンストラクタ (Constructor)
	Player() :  forward(true), x(0.0f), y(0.0f), vx(0.0f), vy(0.0f), ax(0.0f), ay(0.0f), currentState(nullptr){
	}

	// Playerオブジェクトを初期化する (Initialize Player object)
	void Initialize(float x, float y);
	// Playerオブジェクトを更新する (Update Player object)
	bool Update(const DX::StepTimer& timer);
	// プレイヤーオブジェクトの状態を変更する (Change State object)
	void ChangeState(IState* currentState);
	// Playerオブジェクトの状態を描画する (Render Player object)
	void Render(SpriteBatch* spriteBatch);
	// Playerオブジェクトの状態の後処理をおこなう (Finalize Player object)
	void Finalize();
	// デストラクタ (Destructor)
	~Player();

private:
	// 向き
	bool forward;
	// 位置
	float x, y;
	// 速度
	float vx, vy;
	// 加速度
	float ax, ay;
	// 現在の状態
	IState* currentState;
};

#endif // PLAYER_DEFINED
