/*
@brief		プレイシーン
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
	// コンストラクタ (Constructor)
	PlayScene();
	// プレイシーンを初期化する (Initialize PlayScene object)
	void Initialize() override;
	// プレイシーンを更新する (Update PlayScene object)
	void Update(const DX::StepTimer& timer) override;
	// プレイシーンを描画する (Render PlayScene object)
	void Render(DirectX::SpriteBatch* spriteBatch) override;
	// プレイシーンの後始末をする (Finalize PlayScene object)
	void Finalize() override;
	// デストラクタ (Destructor)
	~PlayScene();

private:
	// プレイヤ Player
	Player* player;
	// シーン scene
	//Scene* scene;
};

#endif // PLAYSCENE_DEFINED