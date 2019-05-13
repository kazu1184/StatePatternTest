/*
@brief		�^�C�g���V�[��
@file		TitleScene.cpp
@date		2018/11/25
@author		Shozo Tanaka
*/

//#include "..\Framework\pch.h"
#include "TitleScene.h"

using namespace DX;
using namespace DirectX;

// �R���X�g���N�^ (Constructor)
TitleScene::TitleScene() {
}

// �^�C�g���V�[�������������� (Initialize TitleScene object)
void TitleScene::Initialize() {
}

// �^�C�g���V�[�����X�V���� (Update TitleScene object)
void TitleScene::Update(const StepTimer& timer) {
	// Input�I�u�W�F�N�g���X�V����
	Input::Get()->Update();

	// KeyboardState�I�u�W�F�N�g�ւ̃|�C���^���擾����
	Keyboard::State state = Input::Get()->KeyboardState();
	if (state.IsKeyDown(Keyboard::Space)) {
		// Scene�I�u�W�F�N�g�ւ̃|�C���^���擾����
		Scene* scene =Scene::GetInstance();
		// PlayScene�V�[���ɐ؂�ւ���
		scene->ChangeScene(new PlayScene());
		// �V�[��������������
		scene->Initialize();
	}
}

// �^�C�g���V�[����`�悷�� (Render TitleScene object)
void TitleScene::Render(SpriteBatch* spriteBatch) {
}

// �^�C�g���V�[���̌�n�������� (Finalize TitleScene object)
void TitleScene::Finalize() {
}

// �f�X�g���N�^ (Destructor)
TitleScene::~TitleScene() {
}
