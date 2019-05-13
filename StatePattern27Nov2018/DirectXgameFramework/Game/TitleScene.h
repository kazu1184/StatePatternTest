/*
@brief		タイトルシーン
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

// TitleSceneクラスを宣言する(Declare TitleScene class)
class TitleScene : public Scene {
public:
	// コンストラクタ (Constructor)
	TitleScene();
	// タイトルシーンを初期化する (Initialize TitleScene object) 
	void Initialize() override;
	// タイトルシーンを更新する (Update TitleScene object)
	void Update(const DX::StepTimer& timer) override;
	// タイトルシーンを描画する (Render TitleScene object)
	void Render(DirectX::SpriteBatch* spriteBatch) override;
	// タイトルシーンの後始末をする (Finalize TitleScene object)
	void Finalize() override;
	// デストラクタ
	~TitleScene();

private:
	// Playerオブジェクトへのポインタ Player
	Player* player;
	// Sceneオブジェクトへのポインタ scene
	//Scene* scene;
};

#endif // TITLE_SCENE_DEFINED
