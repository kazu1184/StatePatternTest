/*
@brief		プレイシーン
@file		PlayScene.cpp
@date		2018/11/27
@author		Shozo Tanaka
*/

#include "PlayScene.h"

using namespace DX;
using namespace DirectX;

// コンストラクタ (Constructor)
PlayScene::PlayScene() {
}

// プレイシーンを初期化する (Initialize PlayScene object)
void PlayScene::Initialize() {
	// Playerオブジェクトを生成する (Create Player object)
	this->player = new Player();
	// Playerオブジェクトを初期化する (Initialize Player object)
	this->player->Initialize(START_X, START_Y);
}

// プレイシーンを更新する (Update PlayScene object)
void PlayScene::Update(const StepTimer& timer) {
	// Playerオブジェクトを更新する　(Update Player object)
	this->player->Update(timer);
}

// プレイシーンを描画する (Render PlayerScene object)
inline void PlayScene::Render(SpriteBatch* spriteBatch) {
	// Playerオブジェクトを描画する (Render Player object)
	this->player->Render(spriteBatch);
}

// プレイシーンの後始末をする (Finalize PlayerScene object)
void PlayScene::Finalize() {
	// Playerオブジェクトの後始末をする (Finalize Player object)
	this->player->Finalize();
}

// デストラクタ (Destructor)
PlayScene::~PlayScene() {
	// Playerオブジェクトを破棄する (Delete Player object)
	if (this->player != nullptr) {
		delete this->player;
		this->player = nullptr;
	}
}
