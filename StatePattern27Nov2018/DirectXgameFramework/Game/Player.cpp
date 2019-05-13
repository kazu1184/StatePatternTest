/*
@brief		�v���C���[
@file		Player.cpp
@date		2018/11/27
@author		Shozo Tanaka
*/

#include "Player.h"

using namespace DX;
using namespace DirectX;

// Player�I�u�W�F�N�g������������ (Initialize Player object)
void Player::Initialize(float x, float y) {

	// �v���C���̏�����Ԃ��u�����v�ɐݒ肷�� (Change standing state to initial state)
	ChangeState(Standing::GetInstance());

	// �v���C���̏����ʒu (Intialize initial position(x,y))
	this->x = x;
	this->y = y;

	// �v���C���̏��������x��ݒ肷�� (Initialize accelaration(ax, ay) )
	this->ax = PLAYER_ACCELARATION_X;
	this->ay = PLAYER_ACCELARATION_Y;

	// Standing��Ԃ����������� (Intialize Standing object)
	Standing::GetInstance()->Initialize(this);
	// Jumping��Ԃ����������� (Intialize Jumping object)
	Jumping::GetInstance()->Initialize(this);
	// Ducking��Ԃ����������� (Intialize Ducking object)
	Ducking::GetInstance()->Initialize(this);
	// Running��Ԃ����������� (Intialize Running object)
	Running::GetInstance()->Initialize(this);
}

// Player�I�u�W�F�N�g���X�V���� (Initialize Player object)
bool Player::Update(const StepTimer& timer) {
	// Input�I�u�W�F�N�g���X�V���� (Update Input object)
	Input::Get()->Update();

	// ���݂̏�Ԃ����s���� (Execute current state)
	currentState->Execute(timer);
	return true;
}

// ��Ԃ�ύX���� (Change Player state object)
void Player::ChangeState(IState* currentState) {
	// ���݂̏�Ԃ�ݒ肷��
	this->currentState = currentState;
}

// Player�I�u�W�F�N�g��`�悷�� (Render Player object)
void Player::Render(SpriteBatch* spriteBatch) {
	// ���݂̏�Ԃ�`�悷�� (Draw current state)
	this->currentState->Render(spriteBatch);
}

// Player�I�u�W�F�N�g�̌�n�������� (Finalize player object)
void Player::Finalize() {
	// Standing�I�u�W�F�N�g��j������
	Standing::Dispose();
	// Jumping�I�u�W�F�N�g��j������
	Jumping::Dispose();
	// Ducking�I�u�W�F�N�g��j������
	Ducking::Dispose();
	// Running�I�u�W�F�N�g��j������
	Running::Dispose();
}

// �f�X�g���N�^ (Destructor)
Player::~Player() {
}
