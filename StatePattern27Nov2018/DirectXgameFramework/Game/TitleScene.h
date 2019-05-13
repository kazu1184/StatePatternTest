/*
@brief		�^�C�g���V�[��
@file		TitleScene.h
@date		2018/11/25
@author		Shozo Tanaka
*/

#pragma once
#ifndef TITLE_SCENE_DEFINED
#define TITLE_SCENE_DEFINED

#include "..\\Game\\Scene.h"
#include "..\\Game\\Player.h"
#include "..\\Game\\PlayScene.h"

class Player;

// TitleScene�N���X��錾����(Declare TitleScene class)
class TitleScene : public Scene {
public:
	// �R���X�g���N�^ (Constructor)
	TitleScene();
	// �^�C�g���V�[�������������� (Initialize TitleScene object) 
	void Initialize() override;
	// �^�C�g���V�[�����X�V���� (Update TitleScene object)
	void Update(const DX::StepTimer& timer) override;
	// �^�C�g���V�[����`�悷�� (Render TitleScene object)
	void Render(DirectX::SpriteBatch* spriteBatch) override;
	// �^�C�g���V�[���̌�n�������� (Finalize TitleScene object)
	void Finalize() override;
	// �f�X�g���N�^
	~TitleScene();

private:
	// Player�I�u�W�F�N�g�ւ̃|�C���^ Player
	Player* player;
	// Scene�I�u�W�F�N�g�ւ̃|�C���^ scene
	//Scene* scene;
};

#endif // TITLE_SCENE_DEFINED
