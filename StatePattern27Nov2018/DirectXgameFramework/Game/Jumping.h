/*
@brief		�W�����s���O
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

// Jumping�N���X��錾����
class Jumping : public IState 
{
public:
	// Jumping�N���X�̃C���X�^���X���擾����
	static IState* GetInstance();
	// Jumping�I�u�W�F�N�g������������
	void Initialize(Player* player) override;
	// Jumping�I�u�W�F�N�����s����
	void Execute(const DX::StepTimer& timer) override;
	// Jumping�I�u�W�F�N�g��`�悷��
	void Render(SpriteBatch* spriteBatch) override;
	// Jumping�I�u�W�F�N�g��j������
	static void Dispose();
	
private:
	// �R���X�g���N�^
	Jumping();
	// Jumping�I�u�W�F�N�g�ւ̃|�C���^
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

#endif // JUMPING