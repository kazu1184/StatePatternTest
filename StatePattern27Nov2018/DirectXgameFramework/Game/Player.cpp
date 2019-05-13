/*
@brief		プレイヤー
@file		Player.cpp
@date		2018/11/27
@author		Shozo Tanaka
*/

#include "Player.h"

using namespace DX;
using namespace DirectX;

// Playerオブジェクトを初期化する (Initialize Player object)
void Player::Initialize(float x, float y) {

	// プレイヤの初期状態を「立ち」に設定する (Change standing state to initial state)
	ChangeState(Standing::GetInstance());

	// プレイヤの初期位置 (Intialize initial position(x,y))
	this->x = x;
	this->y = y;

	// プレイヤの初期加速度を設定する (Initialize accelaration(ax, ay) )
	this->ax = PLAYER_ACCELARATION_X;
	this->ay = PLAYER_ACCELARATION_Y;

	// Standing状態を初期化する (Intialize Standing object)
	Standing::GetInstance()->Initialize(this);
	// Jumping状態を初期化する (Intialize Jumping object)
	Jumping::GetInstance()->Initialize(this);
	// Ducking状態を初期化する (Intialize Ducking object)
	Ducking::GetInstance()->Initialize(this);
	// Running状態を初期化する (Intialize Running object)
	Running::GetInstance()->Initialize(this);
}

// Playerオブジェクトを更新する (Initialize Player object)
bool Player::Update(const StepTimer& timer) {
	// Inputオブジェクトを更新する (Update Input object)
	Input::Get()->Update();

	// 現在の状態を実行する (Execute current state)
	currentState->Execute(timer);
	return true;
}

// 状態を変更する (Change Player state object)
void Player::ChangeState(IState* currentState) {
	// 現在の状態を設定する
	this->currentState = currentState;
}

// Playerオブジェクトを描画する (Render Player object)
void Player::Render(SpriteBatch* spriteBatch) {
	// 現在の状態を描画する (Draw current state)
	this->currentState->Render(spriteBatch);
}

// Playerオブジェクトの後始末をする (Finalize player object)
void Player::Finalize() {
	// Standingオブジェクトを破棄する
	Standing::Dispose();
	// Jumpingオブジェクトを破棄する
	Jumping::Dispose();
	// Duckingオブジェクトを破棄する
	Ducking::Dispose();
	// Runningオブジェクトを破棄する
	Running::Dispose();
}

// デストラクタ (Destructor)
Player::~Player() {
}
