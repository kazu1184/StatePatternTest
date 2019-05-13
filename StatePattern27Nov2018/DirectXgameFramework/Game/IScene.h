/*
@brief		シーンインターフェイス
@file		IScene.h
@date		2018/11/25
@author		Shozo Tanaka
*/

#pragma once
#ifndef ISCENE_DEFINED
#define ISCENE_DEFINED

#include <d3d11_1.h>
#include <SpriteBatch.h>
#include "..\\Framework\\StepTimer.h"

// ISceneインターフェイスを宣言する (Declare IScene interface)
class IScene {
public:
	// シーンを初期化する (Initialize object)
	virtual void Initialize() = 0;
	// シーン更新する (Update object)
	virtual void Update(const DX::StepTimer& timer) = 0;
	// シーンを描画する (Render object)
	virtual void Render(DirectX::SpriteBatch* spriteBatch) = 0;
	// シーンを後始末をする (Finalize object)
	virtual void Finalize() = 0;
};

#endif	// ISCENE_DEFINED
