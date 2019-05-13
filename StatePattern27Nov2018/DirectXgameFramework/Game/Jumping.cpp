/*
@brief		ジャンピング
@file		Jumping.cpp
@date		2018/11/25
@author		Shozo Tanaka
*/

#include "Jumping.h"

using namespace DX;
using namespace DirectX;

IState* Jumping::state = nullptr;

// コンストラクタ (Constructor)
Jumping::Jumping() : width(0), height(0) {
}
// Jumpingクラスのインスタンスを取得する (Get instance of Jumping class)
IState* Jumping::GetInstance() {
	if (state == nullptr) {
		// Jumpingオブジェクを生成する
		state = new Jumping();
	}
	return state;
}

// Jumpingオブジェクトを初期化する (Initialize Jumping object)
void Jumping::Initialize(Player* player) {
	// Playerオブジェクトへのポインタをメンバ変数に保管する (Assign player pointer to member variable)
	this->player = player;
	// Textureオブジェクトを生成する (Create Texture object)
	CreateWICTextureFromFile(Graphics::Get().Device().Get(),L"Asset\\jumping.png", nullptr, this->texture.GetAddressOf());

	// Resourceインターフェース (Resource interface)
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	// Textureリソースを取得する (Get Texure resource)
	this->texture->GetResource(resource.GetAddressOf());
	D3D11_RESOURCE_DIMENSION dim;
	// リソースタイプを取得する (Get resource type)
	resource->GetType(&dim);
	// Texture2D内部にアクセスするインターフェース (Interface to access 2D texture)
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
	resource.As(&texture2D);
	D3D11_TEXTURE2D_DESC desc;
	// Texture2Dの記述内容を取得する (Get Texture2D description)
	texture2D->GetDesc(&desc);
	// テクスチャ幅を設定する (Assign texture width)
	this->width = desc.Width;
	// テクスチャ高を設定する (Assign texture height)
	this->height = desc.Height;
}

// Jumpingオブジェクトを実行する (Execute Jumping object)
inline void Jumping::Execute(const StepTimer& timer) {
	// 速度に加速度を加算する Add accelarationto velocity
	this->player->VX( this->player->VX() + this->player->AX());
	this->player->VY(this->player->VY() + this->player->AY());

	// 位置に速度を加算する Add velocity to position
	this->player->X(this->player->X() + this->player->VX());
	this->player->Y(this->player->Y() + this->player->VY());

	// 地面を判定する (Judge ground)
	if (this->player->Y() > GROUND) {
		// 地面の位置を設定する (Assign ground position)
		this->player->Y(GROUND);
		// 速度に0.0を設定する (Assign zero to velocity)
		this->player->VY(0.0f);
	}
	// プレイヤの位置(y座標)が地面(400)に着地した場合 (In case of arriving to ground)
	if (this->player->Y() == GROUND) {
		// キーボードの状態を取得する (Get keyboard state)
		//Keyboard::State state = this->player->KeyboardState();
		Keyboard::State state = Input::Get()->KeyboardState();
		// 「→」キーを押し下げた場合 (In case of pusing down right key)
		if (state.IsKeyDown(Keyboard::Right)) {
			// プレイヤの状態を「走る」に変更する (Change Running state to current state)
			this->player->ChangeState(Running::GetInstance());			
		}
		// 「←」キーを押し下げた場合 (In case of pushing down left key)
		else if (state.IsKeyDown(Keyboard::Left)) {
			// プレイヤの状態を「走る」に変更する (Change Running state to current state)
			this->player->ChangeState(Running::GetInstance());
		}
		else {
			// プレイヤの状態を「立ち」に変更する (Change Standing state to current state)
			this->player->ChangeState(Standing::GetInstance());
		}
	}
}

// Jumpingオブジェクトを描画する (Render Jumping object)
inline void Jumping::Render(SpriteBatch* spriteBatch) {
	// 回転を設定する (Assign zero to rotation)
	float rotation = 0.0f;
	// スケールを設定する(Assign 1.0 to scale)
	float scale = 1.0f;
	// 原点を設定する(Assign width / 2 and height / 2 to origin of texture)
	Vector2 origin = Vector2((float)this->width / 2.0f, (float)this->height / 2.0f);
	// スプライトの効果を設定しない (Assign SpriteEffects_None to sprite effect)
	DirectX::SpriteEffects effects = DirectX::SpriteEffects_None;
	// 後向きかどうかを判定する (Judge player direction)
	if (this->player->Forward() == false) {
		// テクスチャの向きを反転する (Reverse texture direction) 
		effects = DirectX::SpriteEffects_FlipHorizontally;
	}
	// スプライトを描画する　(Draw sprite)
	spriteBatch->Draw(this->texture.Get(), Vector2(player->X(), player->Y()), nullptr, Colors::White, rotation, origin, scale, effects, 0.0f);
}

// Jumpingオブジェクトを破棄する (Delete Standing object)
void Jumping::Dispose() {
	if (state != nullptr) {
		// Jumpingオブジェクトを破棄する
		delete state;
		state = nullptr;
	}
}
