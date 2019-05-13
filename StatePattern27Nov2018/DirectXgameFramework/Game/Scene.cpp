/*
@brief		�V�[��
@file		Scene.cpp
@date		2018/11/25
@author		Shozo Tanaka
*/

#include "Scene.h"

using namespace DX;
using namespace DirectX;

Scene* Scene::scene = nullptr;

// ���������� (Initialize Scene object)
void Scene::Initialize(){
	// ���݂̃V�[��������������
	this->currentScene->Initialize();
}

// �X�V���� (Update Scene object)
void Scene::Update(const StepTimer& timer){
	// ���݂̃V�[�����X�V����
	this->currentScene->Update(timer);
}

// �`�悷�� (Render Scene object)
void Scene::Render(SpriteBatch* spriteBatch){
	// ���݂̃V�[���̕`�������
	this->currentScene->Render(spriteBatch);
}

// ��n�������� (Finalize Scene object)
void Scene::Finalize(){
	// ���݂̃V�[���̌�n��������
	this->currentScene->Finalize();
}

// �f�X�g���N�^ (Destructor)
Scene::~Scene() {
}
