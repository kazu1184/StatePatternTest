/*
@brief		�V�[��
@file		Scene.h
@date		2018/11/27
@author		Shozo Tanaka
*/

#pragma once
#ifndef SCENE_DEFINED
#define SCENE_DEFINED
#include "..\\Game\\IScene.h"
#include "..\\Game\\Player.h"

class Player;

// Scene�N���X��錾���� (Declare Scene class)
class Scene  : public IScene {
protected:
	// �R���X�g���N�^ (Constructor)
	Scene() : currentScene(nullptr) {}

public:
	// Scene�I�u�W�F�N�g�ւ̃|�C���^���擾���� (Get instace of Scene class)
	static Scene* GetInstance() {
		if (scene == nullptr) {
			// Scene�I�u�W�F�N�g�𐶐�����
			scene = new Scene();
		}
		return scene;
	}

	// ���������� (Initialize Scene object)
	virtual void Initialize() override;
	// �X�V���� (Update Scene object)
	virtual void Update(const DX::StepTimer& timer) override;
	// �`�悷�� (Render Scene object)
	virtual void Render(DirectX::SpriteBatch* spriteBatch) override;
	// ��n�������� (Finalize Scene object)
	virtual void Finalize() override;
	// �f�X�g���N�^ (Destructor)
	virtual ~Scene();

	// �V�[����؂�ւ��� (Change Scene object)
	void ChangeScene(Scene* currentScene){
		if (this->currentScene != nullptr) {
			// ���݂�Scene�I�u�W�F�N�g��j������
			delete this->currentScene;
			this->currentScene = nullptr;
		}
		// Scene�I�u�W�F�N�g�ւ̃|�C���^��currentScene�����o�[�ϐ��ɐݒ肷��
		this->currentScene = currentScene;
	}

private:
	// Scene�I�u�W�F�N�g�ւ̃|�C���^
	static Scene* scene;
	// ���݂�Scene�I�u�W�F�N�g�ւ̃|�C���^
	Scene* currentScene;
};

#endif // SCENE_DEFINED

