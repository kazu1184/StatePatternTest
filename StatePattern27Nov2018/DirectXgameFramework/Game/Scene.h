/*
@brief		シーン
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

// Sceneクラスを宣言する (Declare Scene class)
class Scene  : public IScene {
protected:
	// コンストラクタ (Constructor)
	Scene() : currentScene(nullptr) {}

public:
	// Sceneオブジェクトへのポインタを取得する (Get instace of Scene class)
	static Scene* GetInstance() {
		if (scene == nullptr) {
			// Sceneオブジェクトを生成する
			scene = new Scene();
		}
		return scene;
	}

	// 初期化する (Initialize Scene object)
	virtual void Initialize() override;
	// 更新する (Update Scene object)
	virtual void Update(const DX::StepTimer& timer) override;
	// 描画する (Render Scene object)
	virtual void Render(DirectX::SpriteBatch* spriteBatch) override;
	// 後始末をする (Finalize Scene object)
	virtual void Finalize() override;
	// デストラクタ (Destructor)
	virtual ~Scene();

	// シーンを切り替える (Change Scene object)
	void ChangeScene(Scene* currentScene){
		if (this->currentScene != nullptr) {
			// 現在のSceneオブジェクトを破棄する
			delete this->currentScene;
			this->currentScene = nullptr;
		}
		// SceneオブジェクトへのポインタをcurrentSceneメンバー変数に設定する
		this->currentScene = currentScene;
	}

private:
	// Sceneオブジェクトへのポインタ
	static Scene* scene;
	// 現在のSceneオブジェクトへのポインタ
	Scene* currentScene;
};

#endif // SCENE_DEFINED

