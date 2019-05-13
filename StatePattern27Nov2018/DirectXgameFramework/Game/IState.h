/*
@brief		ステートインターフェイス
@file		IState.h
@date		2018/11/25
@author		Shozo Tanaka
*/

#pragma once
#ifndef ISTATE_DEFINED
#define ISTATE_DEFINED

#include "..\\Game\\Player.h"

class Player;

// IStateインターフェイスを宣言する
class IState 
{
public:
	// 状態を初期化する
	virtual void Initialize(Player* player) = 0;
	// 状態を処理を実行する
	virtual void Execute(const DX::StepTimer& timer) = 0;
	// 状態を描画する
	virtual void Render(DirectX::SpriteBatch* spriteBatch) = 0;
};

#endif // ISTATE_DEFINED