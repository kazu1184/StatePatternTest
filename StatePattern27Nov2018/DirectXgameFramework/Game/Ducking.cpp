/*
@brief		屈む
@file		Ducking.cpp
@date		2018/11/25
@author		Shozo Tanaka
*/

#include "Ducking.h"

using namespace DX;
using namespace DirectX;

IState* Ducking::state = nullptr;

// コンストラクタ (Constructor)
Ducking::Ducking() {
}

// Duckingオブジェクトを初期化する (Initialize Ducking object)
void Ducking::Initialize(Player* player) {
	// Playerオブジェクトへのポインタをメンバ変数に保管する (Assign player pointer to member variable)
	this->player = player;

	// Textureオブジェクトを生成する  (Create Texture object)
	CreateWICTextureFromFile(Graphics::Get().Device().Get(), L"Asset\\downing.png", nullptr, this->texture.GetAddressOf());
	// Resourceインターフェース  (Resource interface)
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	// テクスチャのリソースを取得する  (Get Texure resource)
	this->texture->GetResource(resource.GetAddressOf());
	D3D11_RESOURCE_DIMENSION dim;
	// リソースタイプを取得する (Get resource type)
	resource->GetType(&dim);
	// Texture2D内部にアクセスするインターフェース (Interface to access 2D texture)
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
	resource.As(&texture2D);
	D3D11_TEXTURE2D_DESC desc;
	// 2Dテクスチャの記述内容を取得する (Get Texture2D description)
	texture2D->GetDesc(&desc);
	// テクスチャ幅を取得する (Assign texture width)
	this->width = desc.Width;
	// テクスチャ高を取得する (Assign texture height)
	this->height = desc.Height;
}

// Duckingクラスのインスタンスを取得する (Get instance of Ducking class)
IState* Ducking::GetInstance() {
	if (state == nullptr) {
		// Duckingオブジェクを生成する (Create Ducking object)
		state = new Ducking();
	}
	return state;
}

// Duckingオブジェクトを実行する (Execute Ducking object)
inline void Ducking::Execute(const StepTimer& timer) {
	// 「↓」キーを解放した場合 (In case of releasing down key)
	if (Input::Get()->KeyboardStateTracker()->IsKeyReleased(Keyboard::Keys::Down)) {
		// プレイヤの状態を「立ち」に変更する (Change stand state to current state)
		this->player->ChangeState(Standing::GetInstance());
	}
}

// Duckingオブジェクトを描画する (Render Ducking object)
inline void Ducking::Render(SpriteBatch* spriteBatch) {
	// 回転を設定する  (Assign 3.16 to rotation)
	float rotation = PI;
	// スケールを設定する  (Assign -1.0 to scale)
	float scale = -1.0f;
	// 原点を設定する  (Assign width / 2 and height / 2 to origin of texture)
	Vector2 origin = Vector2((float)this->width / 2.0f, (float)this->height / 2.0f);
	// スプライトの効果を設定しない (Assign SpriteEffects_None to sprite effect)
	DirectX::SpriteEffects effects = DirectX::SpriteEffects_None;
	// 後向きかどうか  (Judge player direction)
	if (this->player->Forward() == false) {
		// テクスチャを反転する (Reverse texture direction)
		effects = DirectX::SpriteEffects_FlipHorizontally;
	}
	// テクスチャを描画する (Render texture)
	spriteBatch->Draw(this->texture.Get(), Vector2(player->X(), player->Y()), nullptr, Colors::White, rotation, origin, scale, effects, 0.0f);
}

// Duckingオブジェクトを破棄する (Delete Ducking object)
void Ducking::Dispose() {
	if (state != nullptr) {
		// Duckingオブジェクトをリセットする (Delete Ducking object)
		delete state;
		state = nullptr;
	}
}
