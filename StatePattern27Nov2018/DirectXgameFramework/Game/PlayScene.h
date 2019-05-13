/*
@brief		�v���C�V�[��
@file		PlayScene.h
@date		2018/11/27
@author		Shozo Tanaka
*/

#pragma once
#ifndef PLAY_SCENE
#define PLAY_SCENE

#include "..\\Game\\Scene.h"
#include "..\\Game\\Player.h"

class Player;

class PlayScene : public Scene {
public:
	// �R���X�g���N�^ (Constructor)
	PlayScene();
	// �v���C�V�[�������������� (Initialize PlayScene object)
	void Initialize() override;
	// �v���C�V�[�����X�V���� (Update PlayScene object)
	void Update(const DX::StepTimer& timer) override;
	// �v���C�V�[����`�悷�� (Render PlayScene object)
	void Render(DirectX::SpriteBatch* spriteBatch) override;
	// �v���C�V�[���̌�n�������� (Finalize PlayScene object)
	void Finalize() override;
	// �f�X�g���N�^ (Destructor)
	~PlayScene();

private:
	// �v���C�� Player
	Player* player;
	// �V�[�� scene
	//Scene* scene;
};

#endif // PLAYSCENE_DEFINED