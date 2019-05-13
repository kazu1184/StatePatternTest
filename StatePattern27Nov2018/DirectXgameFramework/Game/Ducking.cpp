/*
@brief		����
@file		Ducking.cpp
@date		2018/11/25
@author		Shozo Tanaka
*/

#include "Ducking.h"

using namespace DX;
using namespace DirectX;

IState* Ducking::state = nullptr;

// �R���X�g���N�^ (Constructor)
Ducking::Ducking() {
}

// Ducking�I�u�W�F�N�g������������ (Initialize Ducking object)
void Ducking::Initialize(Player* player) {
	// Player�I�u�W�F�N�g�ւ̃|�C���^�������o�ϐ��ɕۊǂ��� (Assign player pointer to member variable)
	this->player = player;

	// Texture�I�u�W�F�N�g�𐶐�����  (Create Texture object)
	CreateWICTextureFromFile(Graphics::Get().Device().Get(), L"Asset\\downing.png", nullptr, this->texture.GetAddressOf());
	// Resource�C���^�[�t�F�[�X  (Resource interface)
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	// �e�N�X�`���̃��\�[�X���擾����  (Get Texure resource)
	this->texture->GetResource(resource.GetAddressOf());
	D3D11_RESOURCE_DIMENSION dim;
	// ���\�[�X�^�C�v���擾���� (Get resource type)
	resource->GetType(&dim);
	// Texture2D�����ɃA�N�Z�X����C���^�[�t�F�[�X (Interface to access 2D texture)
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
	resource.As(&texture2D);
	D3D11_TEXTURE2D_DESC desc;
	// 2D�e�N�X�`���̋L�q���e���擾���� (Get Texture2D description)
	texture2D->GetDesc(&desc);
	// �e�N�X�`�������擾���� (Assign texture width)
	this->width = desc.Width;
	// �e�N�X�`�������擾���� (Assign texture height)
	this->height = desc.Height;
}

// Ducking�N���X�̃C���X�^���X���擾���� (Get instance of Ducking class)
IState* Ducking::GetInstance() {
	if (state == nullptr) {
		// Ducking�I�u�W�F�N�𐶐����� (Create Ducking object)
		state = new Ducking();
	}
	return state;
}

// Ducking�I�u�W�F�N�g�����s���� (Execute Ducking object)
inline void Ducking::Execute(const StepTimer& timer) {
	// �u���v�L�[����������ꍇ (In case of releasing down key)
	if (Input::Get()->KeyboardStateTracker()->IsKeyReleased(Keyboard::Keys::Down)) {
		// �v���C���̏�Ԃ��u�����v�ɕύX���� (Change stand state to current state)
		this->player->ChangeState(Standing::GetInstance());
	}
}

// Ducking�I�u�W�F�N�g��`�悷�� (Render Ducking object)
inline void Ducking::Render(SpriteBatch* spriteBatch) {
	// ��]��ݒ肷��  (Assign 3.16 to rotation)
	float rotation = PI;
	// �X�P�[����ݒ肷��  (Assign -1.0 to scale)
	float scale = -1.0f;
	// ���_��ݒ肷��  (Assign width / 2 and height / 2 to origin of texture)
	Vector2 origin = Vector2((float)this->width / 2.0f, (float)this->height / 2.0f);
	// �X�v���C�g�̌��ʂ�ݒ肵�Ȃ� (Assign SpriteEffects_None to sprite effect)
	DirectX::SpriteEffects effects = DirectX::SpriteEffects_None;
	// ��������ǂ���  (Judge player direction)
	if (this->player->Forward() == false) {
		// �e�N�X�`���𔽓]���� (Reverse texture direction)
		effects = DirectX::SpriteEffects_FlipHorizontally;
	}
	// �e�N�X�`����`�悷�� (Render texture)
	spriteBatch->Draw(this->texture.Get(), Vector2(player->X(), player->Y()), nullptr, Colors::White, rotation, origin, scale, effects, 0.0f);
}

// Ducking�I�u�W�F�N�g��j������ (Delete Ducking object)
void Ducking::Dispose() {
	if (state != nullptr) {
		// Ducking�I�u�W�F�N�g�����Z�b�g���� (Delete Ducking object)
		delete state;
		state = nullptr;
	}
}
