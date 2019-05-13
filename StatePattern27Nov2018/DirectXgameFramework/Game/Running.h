/*
@brief		�����j���O
@file		Running.h
@date		2018/11/25
@author		Shozo Tanaka
*/

#pragma once
#ifndef RUNNING_DEFINED
#define RUNNING_DEFINED

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
#include "..\\Game\\AnimatedTexture.h"

class IState;
class Player;

// Running�N���X��錾���� (Declare Standing class)
class Running : public IState {
public:
	// Running�N���X�̃C���X�^���X���擾���� (Get instance of Running class)
	static IState* GetInstance();
	// Running�I�u�W�F�N�g������������ (Initialize Running object)
	void Initialize(Player* player) override;
	// Running�I�u�W�F�N�g�����s���� (Execute Running object)
	void Execute(const DX::StepTimer& timer) override;
	// Running�I�u�W�F�N�g��`�悷�� (Render Running object)
	void Render(SpriteBatch* spriteBatch) override;
	// Running�I�u�W�F�N�g��j������ (Delete Running object)
	static void Dispose();
	// �f�X�g���N�^ (Destructor)
	~Running();

private:
	// �R���X�g���N�^
	Running();
	// Running�I�u�W�F�N�g�ւ̃|�C���^
	static IState* state;
	// Player�I�u�W�F�N�g�ւ̃|�C���^
	Player* player;
	// �`�悵�Ă���e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	// AnimationTexure�I�u�W�F�N�g�ւ̃|�C���^
	AnimatedTexture* animatedTexture;
	// �e�N�X�`����
	int width;
	// �e�N�X�`����
	int height;
};

#endif // RUNNING_DEFINED