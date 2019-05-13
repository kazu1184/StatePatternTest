/*
@brief		ランニング
@file		Running.cpp
@date		2018/11/25
@author		Shozo Tanaka
*/

#include "Running.h"

using namespace DX;
using namespace DirectX;

IState* Running::state = nullptr;

// コンストラクタ (Constructor)
Running::Running() {
}

// Runningオブジェクトを初期化する (Initialize Running object)
void Running::Initialize(Player* player) {
	// Playerオブジェクトへのポインタをメンバ変数に保管する (Assign player pointer to member variable)
	this->player = player;

	// Textureオブジェクトを生成する (Create Texture object)
	CreateWICTextureFromFile(Graphics::Get().Device().Get(), L"Asset\\running.png", nullptr, this->texture.GetAddressOf());

	// AnimatedTextureオブジェクトを生成する (Create animated texture object)
	this->animatedTexture = new AnimatedTexture(XMFLOAT2(0.0f, 0.0f), 0.0f, 1.0f, 0.5f);
	// アニメーションテクスチャをロードする (Load animated texture)
	this->animatedTexture->Load(this->texture.Get(), 3, 10);
}

// Runningクラスのインスタンスを取得する (Get instance of Running class)
IState* Running::GetInstance() {
	if (state == nullptr) {
		// Runningオブジェクを生成する (Create Running object)
		state = new Running();
	}
	return state;
}

// Runningオブジェクトを実行する (Execute Running object)
inline void Running::Execute(const StepTimer& timer) {
	// アニメーションスプライトを更新する (Update animated sprite)
	this->animatedTexture->Update((float)timer.GetElapsedSeconds());
	// 「スペース」キーを押し下げた場合 (In case of pussing down space key)
	if (Input::Get()->KeyboardStateTracker()->IsKeyPressed(Keyboard::Keys::Space)) {
		// 速度が0より大きい場合 (In case of velocity(vx) > 0)
		if (this->player->VX() > 0) {
			// 速度(vx)に初期値を設定する (Assign initial velocity(vx)) 
			this->player->VX(JUMP_SPEED_X);
		} 
		// 速度が0より大きい場合 (In case of velocity(vx) < 0)
		else if (this->player->VX() < 0) {
			// 速度(vx)に初期値を設定する (Assign initial velocity(vx))
			this->player->VX(-JUMP_SPEED_X);
		}
		// 速度(vy)に初期値を設定する (Assign initial velocity(vy))
		this->player->VY(-JUMP_SPEED_Y);
		// プレイヤの状態を「飛ぶ」に変更する (Change jump state to current state)
		this->player->ChangeState(Jumping::GetInstance());
	}
	// 「→」キーまたは「←」キーを解放した場合 (In case of releasing right and left key)
	if (Input::Get()->KeyboardStateTracker()->IsKeyReleased(Keyboard::Keys::Right) ||
		Input::Get()->KeyboardStateTracker()->IsKeyReleased(Keyboard::Keys::Left)) {
		// プレイヤの状態を「立ち」に変更する (Change stand state to current state)
		this->player->ChangeState(Standing::GetInstance());
		// 静止する (Assign zero to velociy(vx))
		this->player->VX(0.0);
	}
	// 位置に速度を加算する (Add velocity(vx) to position)
	this->player->X(this->player->X() + this->player->VX());
}

// Runningオブジェクトを描画する (Render Running object)
inline void Running::Render(SpriteBatch* spriteBatch) {
	// アニメーションテクスチャを描画する (Render animated texture)
	this->animatedTexture->Draw(spriteBatch, Vector2(this->player->X(), this->player->Y()), player->VX());
}

// Runningオブジェクトを破棄する (Delete Running object)
void Running::Dispose() {	
	if (state != nullptr) {
		// Runningオブジェクトを破棄する (Delete Running object)
		delete state;
		state = nullptr;
	}
}

// デストラクタ (Destructor)
Running::~Running() {
	if (this->animatedTexture != nullptr)
		// AnimationTexureオブジェクトを破棄する
		delete this->animatedTexture;
	this->animatedTexture = nullptr;
}
