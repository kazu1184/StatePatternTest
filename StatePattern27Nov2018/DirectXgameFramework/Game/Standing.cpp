/*
@brief		�X�^���f�B���O
@file		Standing.cpp
@date		2018/11/27
@author		Shozo Tanaka
*/

#include "Standing.h" 

using namespace DX;
using namespace DirectX;

IState* Standing::state = nullptr;

// �R���X�g���N�^ (Constructor)
Standing::Standing() : width(0), height(0) {
}

// Standing�I�u�W�F�N�g������������ (Initialize Standing object)
void Standing::Initialize(Player* player) {
	// Player�I�u�W�F�N�g�ւ̃|�C���^�������o�ϐ��ɕۊǂ��� (Assign player pointer to member variable)
	this->player = player;

	// Texture�I�u�W�F�N�g�𐶐����� (Create Texture object)
	CreateWICTextureFromFile(Graphics::Get().Device().Get(), L"Asset\\standing.png", nullptr, this->texture.GetAddressOf());

	// Resource�C���^�[�t�F�[�X (Resource interface)
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	// �e�N�X�`���̃��\�[�X���擾���� (Get Texure resource)
	this->texture->GetResource(resource.GetAddressOf());

	// �g�p���̃��\�[�X�^�C�v�̎��� (Resource dimension)
	D3D11_RESOURCE_DIMENSION dim;
	// ���\�[�X�^�C�v���擾���� (Get resource type)
	resource->GetType(&dim);
	// Texture2D�����ɃA�N�Z�X����C���^�[�t�F�[�X (Interface to access 2D texture)
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
	resource.As(&texture2D);

	// 2D�e�N�X�`���[�ɂ��Ă̋L�q
	D3D11_TEXTURE2D_DESC desc;
	// 2D�e�N�X�`���̋L�q���e���擾���� (Get Texture2D description)
	texture2D->GetDesc(&desc);
	// �e�N�X�`������ݒ肷�� (Assign texture width)
	this->width = desc.Width;  
	// �e�N�X�`������ݒ肷��  (Assign texture height)
	this->height = desc.Height;
}

// Standing�N���X�̃C���X�^���X���擾���� (Get instance of Standing class)
IState* Standing::GetInstance() {
	if (state == nullptr) {
		// Standing�I�u�W�F�N�𐶐����� (Create Standing object)
		state = new Standing();
	}
	return state;
}

// Standing�I�u�W�F�N�g�����s���� (Execute Standing object)
inline void Standing::Execute(const StepTimer& timer) {
	// �u�X�y�[�X�v�L�[�������������ꍇ (In case of pushing down space key)
	if(Input::Get()->KeyboardStateTracker()->IsKeyPressed(Keyboard::Keys::Space)){
		// �v���C���̏�Ԃ��u�W�����v�v�ɕύX���� (Change Jumping state to current state)
		this->player->ChangeState(Jumping::GetInstance());
		// ���x(vx)�ɏ����l(0.0f)��ݒ肷�� (Assign zero to jump velocity(vx))
		this->player->VX(0.0f);
		// ���x(vy)�ɏ����l(-10.0f)��ݒ肷�� (Assign JUMP_VELOCITY_Y to jump velocity(vy))
		this->player->VY(-JUMP_SPEED_Y);
	}
	// �u���v�L�[�������������ꍇ  (In case of pushing down down key)
	else if (Input::Get()->KeyboardStateTracker()->IsKeyPressed(Keyboard::Keys::Down)) {
		// �v���C���̏�Ԃ��u���ށv�ɕύX���� (Change Ducking to current state)
		this->player->ChangeState(Ducking::GetInstance());
	}
	// �u���v�L�[�������������ꍇ  (In case of pushing down right key)
	else if (Input::Get()->KeyboardStateTracker()->IsKeyPressed(Keyboard::Keys::Right)) {
		// ���x(VX)�ɑ��s���x(4)��ݒ肷�� (Assign RUNNING_VELOCITY_X to run velocity(vx))
		this->player->VX(RUNNING_SPEED_X);
		// �v���C���̏�Ԃ��u����v�ɕύX���� (Change Running state to current state)
		this->player->ChangeState(Running::GetInstance());
		// ������O���ɐݒ肷�� (Set forward direction to player direction)
		this->player->Forward(true);
	}
	// �u���v�L�[�������������ꍇ  (In case of pushing down left key)
	else if (Input::Get()->KeyboardStateTracker()->IsKeyPressed(Keyboard::Keys::Left)) {
		this->player->VX(-RUNNING_SPEED_X);
		// �v���C���̏�Ԃ��u����v�ɕύX���� Change Running state to current state)
		this->player->ChangeState(Running::GetInstance());
		// ����������ɐݒ肷�� (Set backward direction to player direction)
		this->player->Forward(false);
	}
}

// Standing�I�u�W�F�N�g��`�悷�� (Render Standing object)
inline void Standing::Render(SpriteBatch* spriteBatch) {
	// ��]��ݒ肷��  (Assign 3.16 to rotation)
	float rotation = PI;
	// �X�P�[����ݒ肷�� (Assign -1.0 to scale)
	float scale = -1.0f;
	// ���_��ݒ肷�� (Assign width / 2 and height / 2 to origin of texture)
	Vector2 origin = Vector2((float)this->width / 2.0f, (float)this->height / 2.0f);
	// �X�v���C�g�̌��ʂ�ݒ肵�Ȃ� (Assign SpriteEffects_None to sprite effect)
	SpriteEffects effects = DirectX::SpriteEffects_None;
	// ��������ǂ���  (Judge player direction)
	if (this->player->Forward() == false) {
		// �e�N�X�`���𔽓]���� (Reverse texture direction)
		effects = SpriteEffects_FlipHorizontally;
	}
	// �e�N�X�`����`�悷�� (Draw texture)
	spriteBatch->Draw(this->texture.Get(), Vector2(player->X(), player->Y()), nullptr, Colors::White, rotation, origin, scale, effects, 0.0f);
}

// Standing�I�u�W�F�N�g��j������ (Delete Standing object)
void Standing::Dispose() {
	if (state != nullptr) {
		// Standing�I�u�W�F�N�g��j������
		delete state;
		state = nullptr;
	}
}