/*
@brief		�v���C�V�[��
@file		PlayScene.cpp
@date		2018/11/27
@author		Shozo Tanaka
*/

#include "PlayScene.h"

using namespace DX;
using namespace DirectX;

// �R���X�g���N�^ (Constructor)
PlayScene::PlayScene() {
}

// �v���C�V�[�������������� (Initialize PlayScene object)
void PlayScene::Initialize() {
	// Player�I�u�W�F�N�g�𐶐����� (Create Player object)
	this->player = new Player();
	// Player�I�u�W�F�N�g������������ (Initialize Player object)
	this->player->Initialize(START_X, START_Y);
}

// �v���C�V�[�����X�V���� (Update PlayScene object)
void PlayScene::Update(const StepTimer& timer) {
	// Player�I�u�W�F�N�g���X�V����@(Update Player object)
	this->player->Update(timer);
}

// �v���C�V�[����`�悷�� (Render PlayerScene object)
inline void PlayScene::Render(SpriteBatch* spriteBatch) {
	// Player�I�u�W�F�N�g��`�悷�� (Render Player object)
	this->player->Render(spriteBatch);
}

// �v���C�V�[���̌�n�������� (Finalize PlayerScene object)
void PlayScene::Finalize() {
	// Player�I�u�W�F�N�g�̌�n�������� (Finalize Player object)
	this->player->Finalize();
}

// �f�X�g���N�^ (Destructor)
PlayScene::~PlayScene() {
	// Player�I�u�W�F�N�g��j������ (Delete Player object)
	if (this->player != nullptr) {
		delete this->player;
		this->player = nullptr;
	}
}
