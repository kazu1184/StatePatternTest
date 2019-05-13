/*
@brief		シーン
@file		Scene.cpp
@date		2018/11/25
@author		Shozo Tanaka
*/

#include "Scene.h"

using namespace DX;
using namespace DirectX;

Scene* Scene::scene = nullptr;

// 初期化する (Initialize Scene object)
void Scene::Initialize(){
	// 現在のシーンを初期化する
	this->currentScene->Initialize();
}

// 更新する (Update Scene object)
void Scene::Update(const StepTimer& timer){
	// 現在のシーンを更新する
	this->currentScene->Update(timer);
}

// 描画する (Render Scene object)
void Scene::Render(SpriteBatch* spriteBatch){
	// 現在のシーンの描画をする
	this->currentScene->Render(spriteBatch);
}

// 後始末をする (Finalize Scene object)
void Scene::Finalize(){
	// 現在のシーンの後始末をする
	this->currentScene->Finalize();
}

// デストラクタ (Destructor)
Scene::~Scene() {
}
