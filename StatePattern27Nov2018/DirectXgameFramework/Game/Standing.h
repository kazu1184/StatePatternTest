/*
@brief		�X�^���f�B���O
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

// Standing�N���X��錾���� (Declare Standing class)
class Standing : public IState {
public:
	// Standing�N���X�̃C���X�^���X���擾���� (Get instance of Standing class)
	static IState* GetInstance();
	// Standing�I�u�W�F�N�g������������ (Initialize Standing object)
	void Initialize(Player* player) override;
	// Standing�I�u�W�F�N�g�����s���� (Execute Standing object)
	void Execute(const DX::StepTimer& timer) override;
	// Standing�I�u�W�F�N�g��`�悷�� (Render Standing object)
	void Render(SpriteBatch* spriteBatch) override;
	// Standing�I�u�W�F�N�g��j������ (Delete Standing object)
	static void Dispose();

private:
	// �R���X�g���N�^
	Standing();
	// Stanging�I�u�W�F�N�g�ւ̃|�C���^
	static IState* state;
	// Player�I�u�W�F�N�g�ւ̃|�C���^
	Player* player;
	// �e�N�X�`���I�u�W�F�N�g�ւ̃|�C���^
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	// �e�N�X�`����
	int width;
	// �e�N�X�`����
	int height;
};

#endif // STANDING_DEFINED