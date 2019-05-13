/*
@brief		�V�[���C���^�[�t�F�C�X
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

// IScene�C���^�[�t�F�C�X��錾���� (Declare IScene interface)
class IScene {
public:
	// �V�[�������������� (Initialize object)
	virtual void Initialize() = 0;
	// �V�[���X�V���� (Update object)
	virtual void Update(const DX::StepTimer& timer) = 0;
	// �V�[����`�悷�� (Render object)
	virtual void Render(DirectX::SpriteBatch* spriteBatch) = 0;
	// �V�[������n�������� (Finalize object)
	virtual void Finalize() = 0;
};

#endif	// ISCENE_DEFINED
