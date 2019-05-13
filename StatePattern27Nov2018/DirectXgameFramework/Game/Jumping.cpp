/*
@brief		�W�����s���O
@file		Jumping.cpp
@date		2018/11/25
@author		Shozo Tanaka
*/

#include "Jumping.h"

using namespace DX;
using namespace DirectX;

IState* Jumping::state = nullptr;

// �R���X�g���N�^ (Constructor)
Jumping::Jumping() : width(0), height(0) {
}
// Jumping�N���X�̃C���X�^���X���擾���� (Get instance of Jumping class)
IState* Jumping::GetInstance() {
	if (state == nullptr) {
		// Jumping�I�u�W�F�N�𐶐�����
		state = new Jumping();
	}
	return state;
}

// Jumping�I�u�W�F�N�g������������ (Initialize Jumping object)
void Jumping::Initialize(Player* player) {
	// Player�I�u�W�F�N�g�ւ̃|�C���^�������o�ϐ��ɕۊǂ��� (Assign player pointer to member variable)
	this->player = player;
	// Texture�I�u�W�F�N�g�𐶐����� (Create Texture object)
	CreateWICTextureFromFile(Graphics::Get().Device().Get(),L"Asset\\jumping.png", nullptr, this->texture.GetAddressOf());

	// Resource�C���^�[�t�F�[�X (Resource interface)
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	// Texture���\�[�X���擾���� (Get Texure resource)
	this->texture->GetResource(resource.GetAddressOf());
	D3D11_RESOURCE_DIMENSION dim;
	// ���\�[�X�^�C�v���擾���� (Get resource type)
	resource->GetType(&dim);
	// Texture2D�����ɃA�N�Z�X����C���^�[�t�F�[�X (Interface to access 2D texture)
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
	resource.As(&texture2D);
	D3D11_TEXTURE2D_DESC desc;
	// Texture2D�̋L�q���e���擾���� (Get Texture2D description)
	texture2D->GetDesc(&desc);
	// �e�N�X�`������ݒ肷�� (Assign texture width)
	this->width = desc.Width;
	// �e�N�X�`������ݒ肷�� (Assign texture height)
	this->height = desc.Height;
}

// Jumping�I�u�W�F�N�g�����s���� (Execute Jumping object)
inline void Jumping::Execute(const StepTimer& timer) {
	// ���x�ɉ����x�����Z���� Add accelarationto velocity
	this->player->VX( this->player->VX() + this->player->AX());
	this->player->VY(this->player->VY() + this->player->AY());

	// �ʒu�ɑ��x�����Z���� Add velocity to position
	this->player->X(this->player->X() + this->player->VX());
	this->player->Y(this->player->Y() + this->player->VY());

	// �n�ʂ𔻒肷�� (Judge ground)
	if (this->player->Y() > GROUND) {
		// �n�ʂ̈ʒu��ݒ肷�� (Assign ground position)
		this->player->Y(GROUND);
		// ���x��0.0��ݒ肷�� (Assign zero to velocity)
		this->player->VY(0.0f);
	}
	// �v���C���̈ʒu(y���W)���n��(400)�ɒ��n�����ꍇ (In case of arriving to ground)
	if (this->player->Y() == GROUND) {
		// �L�[�{�[�h�̏�Ԃ��擾���� (Get keyboard state)
		//Keyboard::State state = this->player->KeyboardState();
		Keyboard::State state = Input::Get()->KeyboardState();
		// �u���v�L�[�������������ꍇ (In case of pusing down right key)
		if (state.IsKeyDown(Keyboard::Right)) {
			// �v���C���̏�Ԃ��u����v�ɕύX���� (Change Running state to current state)
			this->player->ChangeState(Running::GetInstance());			
		}
		// �u���v�L�[�������������ꍇ (In case of pushing down left key)
		else if (state.IsKeyDown(Keyboard::Left)) {
			// �v���C���̏�Ԃ��u����v�ɕύX���� (Change Running state to current state)
			this->player->ChangeState(Running::GetInstance());
		}
		else {
			// �v���C���̏�Ԃ��u�����v�ɕύX���� (Change Standing state to current state)
			this->player->ChangeState(Standing::GetInstance());
		}
	}
}

// Jumping�I�u�W�F�N�g��`�悷�� (Render Jumping object)
inline void Jumping::Render(SpriteBatch* spriteBatch) {
	// ��]��ݒ肷�� (Assign zero to rotation)
	float rotation = 0.0f;
	// �X�P�[����ݒ肷��(Assign 1.0 to scale)
	float scale = 1.0f;
	// ���_��ݒ肷��(Assign width / 2 and height / 2 to origin of texture)
	Vector2 origin = Vector2((float)this->width / 2.0f, (float)this->height / 2.0f);
	// �X�v���C�g�̌��ʂ�ݒ肵�Ȃ� (Assign SpriteEffects_None to sprite effect)
	DirectX::SpriteEffects effects = DirectX::SpriteEffects_None;
	// ��������ǂ����𔻒肷�� (Judge player direction)
	if (this->player->Forward() == false) {
		// �e�N�X�`���̌����𔽓]���� (Reverse texture direction) 
		effects = DirectX::SpriteEffects_FlipHorizontally;
	}
	// �X�v���C�g��`�悷��@(Draw sprite)
	spriteBatch->Draw(this->texture.Get(), Vector2(player->X(), player->Y()), nullptr, Colors::White, rotation, origin, scale, effects, 0.0f);
}

// Jumping�I�u�W�F�N�g��j������ (Delete Standing object)
void Jumping::Dispose() {
	if (state != nullptr) {
		// Jumping�I�u�W�F�N�g��j������
		delete state;
		state = nullptr;
	}
}
