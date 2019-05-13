/*
@brief		�v���C���[
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

// Player�N���X��錾���� (Declare Player class)
class Player {
public:
	// �������擾����
	bool Forward() { return this->forward; }
	// ������ݒ肷��
	void Forward(bool forward) { this->forward = forward; }
	// x���W���擾����
	float X() { return this->x; }
	// x���W��ݒ肷��
	void  X(float x) { this->x = x; }
	// y���W���擾����
	float Y() { return this->y; }
	// y���W��ݒ肷��
	void  Y(float y) { this->y = y; }

	// ���x(vx)���擾����
	float VX() { return this->vx; }
	// ���x(vy)��ݒ肷��
	void  VX(float vx) { this->vx = vx; }
	// ���x(vx)���擾����
	float VY() { return this->vy; }
	// ���x(vy)��ݒ肷��
	void  VY(float vy) { this->vy = vy; }

	// �����x(ax)���擾����
	float AX() { return this->ax; }
	// �����x(ax)��ݒ肷��
	void AX(float ax) { this->ax = ax; }
	// �����x(ay)���擾����
	float AY() { return this->ay; }
	// �����x(ay)��ݒ肷��
	void AY(float ay) { this->ay = ay; }

	// �R���X�g���N�^ (Constructor)
	Player() :  forward(true), x(0.0f), y(0.0f), vx(0.0f), vy(0.0f), ax(0.0f), ay(0.0f), currentState(nullptr){
	}

	// Player�I�u�W�F�N�g������������ (Initialize Player object)
	void Initialize(float x, float y);
	// Player�I�u�W�F�N�g���X�V���� (Update Player object)
	bool Update(const DX::StepTimer& timer);
	// �v���C���[�I�u�W�F�N�g�̏�Ԃ�ύX���� (Change State object)
	void ChangeState(IState* currentState);
	// Player�I�u�W�F�N�g�̏�Ԃ�`�悷�� (Render Player object)
	void Render(SpriteBatch* spriteBatch);
	// Player�I�u�W�F�N�g�̏�Ԃ̌㏈���������Ȃ� (Finalize Player object)
	void Finalize();
	// �f�X�g���N�^ (Destructor)
	~Player();

private:
	// ����
	bool forward;
	// �ʒu
	float x, y;
	// ���x
	float vx, vy;
	// �����x
	float ax, ay;
	// ���݂̏��
	IState* currentState;
};

#endif // PLAYER_DEFINED
