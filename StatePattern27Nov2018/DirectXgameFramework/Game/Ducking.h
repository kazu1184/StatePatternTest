/*
@brief		����
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

// Ducking�N���X��錾����(Declare Ducking class)
class Ducking : public IState {
public:
	// Ducking�N���X�̃C���X�^���X���擾���� (Get instance of Ducking class
	static IState* GetInstance();
	// Ducking�I�u�W�F�N�g������������ (Initialize Ducking object)
	void Initialize(Player* player) override;
	// Ducking�I�u�W�F�N�g�����s���� (Execute Ducking object)
	void Execute(const DX::StepTimer& timer) override;
	// Ducking�I�u�W�F�N�g��`�悷�� (Render Ducking object)
	void Render(SpriteBatch* spriteBatch) override;
	// Ducking�I�u�W�F�N�g��j������ (Delete Ducking object)
	static void Dispose();

private:
	// �R���X�g���N�^
	Ducking();
	// Ducking�I�u�W�F�N�g�ւ̃|�C���^
	static IState* state;
	// Player�I�u�W�F�N�g�ւ̃|�C���^
	Player* player;
	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	// �e�N�X�`����
	int width;
	// �e�N�X�`����
	int height;
};

#endif // DUCKING_DEFINED