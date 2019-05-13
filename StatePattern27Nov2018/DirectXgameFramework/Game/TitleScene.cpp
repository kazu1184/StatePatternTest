/*
@brief		タイトルシーン
@file		TitleScene.cpp
@date		2018/11/25
@author		Shozo Tanaka
*/

//#include "..\Framework\pch.h"
#include "TitleScene.h"

using namespace DX;
using namespace DirectX;

// コンストラクタ (Constructor)
TitleScene::TitleScene() {
}

// タイトルシーンを初期化する (Initialize TitleScene object)
void TitleScene::Initialize() {
}

// タイトルシーンを更新する (Update TitleScene object)
void TitleScene::Update(const StepTimer& timer) {
	// Inputオブジェクトを更新する
	Input::Get()->Update();

	// KeyboardStateオブジェクトへのポインタを取得する
	Keyboard::State state = Input::Get()->KeyboardState();
	if (state.IsKeyDown(Keyboard::Space)) {
		// Sceneオブジェクトへのポインタを取得する
		Scene* scene =Scene::GetInstance();
		// PlaySceneシーンに切り替える
		scene->ChangeScene(new PlayScene());
		// シーンを初期化する
		scene->Initialize();
	}
}

// タイトルシーンを描画する (Render TitleScene object)
void TitleScene::Render(SpriteBatch* spriteBatch) {
}

// タイトルシーンの後始末をする (Finalize TitleScene object)
void TitleScene::Finalize() {
}

// デストラクタ (Destructor)
TitleScene::~TitleScene() {
}
