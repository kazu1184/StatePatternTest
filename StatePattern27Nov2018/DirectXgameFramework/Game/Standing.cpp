/*
@brief		スタンディング
@file		Standing.cpp
@date		2018/11/27
@author		Shozo Tanaka
*/

#include "Standing.h" 

using namespace DX;
using namespace DirectX;

IState* Standing::state = nullptr;

// コンストラクタ (Constructor)
Standing::Standing() : width(0), height(0) {
}

// Standingオブジェクトを初期化する (Initialize Standing object)
void Standing::Initialize(Player* player) {
	// Playerオブジェクトへのポインタをメンバ変数に保管する (Assign player pointer to member variable)
	this->player = player;

	// Textureオブジェクトを生成する (Create Texture object)
	CreateWICTextureFromFile(Graphics::Get().Device().Get(), L"Asset\\standing.png", nullptr, this->texture.GetAddressOf());

	// Resourceインターフェース (Resource interface)
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	// テクスチャのリソースを取得する (Get Texure resource)
	this->texture->GetResource(resource.GetAddressOf());

	// 使用中のリソースタイプの識別 (Resource dimension)
	D3D11_RESOURCE_DIMENSION dim;
	// リソースタイプを取得する (Get resource type)
	resource->GetType(&dim);
	// Texture2D内部にアクセスするインターフェース (Interface to access 2D texture)
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
	resource.As(&texture2D);

	// 2Dテクスチャーについての記述
	D3D11_TEXTURE2D_DESC desc;
	// 2Dテクスチャの記述内容を取得する (Get Texture2D description)
	texture2D->GetDesc(&desc);
	// テクスチャ幅を設定する (Assign texture width)
	this->width = desc.Width;  
	// テクスチャ高を設定する  (Assign texture height)
	this->height = desc.Height;
}

// Standingクラスのインスタンスを取得する (Get instance of Standing class)
IState* Standing::GetInstance() {
	if (state == nullptr) {
		// Standingオブジェクを生成する (Create Standing object)
		state = new Standing();
	}
	return state;
}

// Standingオブジェクトを実行する (Execute Standing object)
inline void Standing::Execute(const StepTimer& timer) {
	// 「スペース」キーを押し下げた場合 (In case of pushing down space key)
	if(Input::Get()->KeyboardStateTracker()->IsKeyPressed(Keyboard::Keys::Space)){
		// プレイヤの状態を「ジャンプ」に変更する (Change Jumping state to current state)
		this->player->ChangeState(Jumping::GetInstance());
		// 速度(vx)に初期値(0.0f)を設定する (Assign zero to jump velocity(vx))
		this->player->VX(0.0f);
		// 速度(vy)に初期値(-10.0f)を設定する (Assign JUMP_VELOCITY_Y to jump velocity(vy))
		this->player->VY(-JUMP_SPEED_Y);
	}
	// 「↓」キーを押し下げた場合  (In case of pushing down down key)
	else if (Input::Get()->KeyboardStateTracker()->IsKeyPressed(Keyboard::Keys::Down)) {
		// プレイヤの状態を「屈む」に変更する (Change Ducking to current state)
		this->player->ChangeState(Ducking::GetInstance());
	}
	// 「→」キーを押し下げた場合  (In case of pushing down right key)
	else if (Input::Get()->KeyboardStateTracker()->IsKeyPressed(Keyboard::Keys::Right)) {
		// 速度(VX)に走行速度(4)を設定する (Assign RUNNING_VELOCITY_X to run velocity(vx))
		this->player->VX(RUNNING_SPEED_X);
		// プレイヤの状態を「走る」に変更する (Change Running state to current state)
		this->player->ChangeState(Running::GetInstance());
		// 向きを前方に設定する (Set forward direction to player direction)
		this->player->Forward(true);
	}
	// 「←」キーを押し下げた場合  (In case of pushing down left key)
	else if (Input::Get()->KeyboardStateTracker()->IsKeyPressed(Keyboard::Keys::Left)) {
		this->player->VX(-RUNNING_SPEED_X);
		// プレイヤの状態を「走る」に変更する Change Running state to current state)
		this->player->ChangeState(Running::GetInstance());
		// 向きを後方に設定する (Set backward direction to player direction)
		this->player->Forward(false);
	}
}

// Standingオブジェクトを描画する (Render Standing object)
inline void Standing::Render(SpriteBatch* spriteBatch) {
	// 回転を設定する  (Assign 3.16 to rotation)
	float rotation = PI;
	// スケールを設定する (Assign -1.0 to scale)
	float scale = -1.0f;
	// 原点を設定する (Assign width / 2 and height / 2 to origin of texture)
	Vector2 origin = Vector2((float)this->width / 2.0f, (float)this->height / 2.0f);
	// スプライトの効果を設定しない (Assign SpriteEffects_None to sprite effect)
	SpriteEffects effects = DirectX::SpriteEffects_None;
	// 後向きかどうか  (Judge player direction)
	if (this->player->Forward() == false) {
		// テクスチャを反転する (Reverse texture direction)
		effects = SpriteEffects_FlipHorizontally;
	}
	// テクスチャを描画する (Draw texture)
	spriteBatch->Draw(this->texture.Get(), Vector2(player->X(), player->Y()), nullptr, Colors::White, rotation, origin, scale, effects, 0.0f);
}

// Standingオブジェクトを破棄する (Delete Standing object)
void Standing::Dispose() {
	if (state != nullptr) {
		// Standingオブジェクトを破棄する
		delete state;
		state = nullptr;
	}
}