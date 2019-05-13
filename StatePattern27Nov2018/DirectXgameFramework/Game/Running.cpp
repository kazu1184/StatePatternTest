/*
@brief		�����j���O
@file		Running.cpp
@date		2018/11/25
@author		Shozo Tanaka
*/

#include "Running.h"

using namespace DX;
using namespace DirectX;

IState* Running::state = nullptr;

// �R���X�g���N�^ (Constructor)
Running::Running() {
}

// Running�I�u�W�F�N�g������������ (Initialize Running object)
void Running::Initialize(Player* player) {
	// Player�I�u�W�F�N�g�ւ̃|�C���^�������o�ϐ��ɕۊǂ��� (Assign player pointer to member variable)
	this->player = player;

	// Texture�I�u�W�F�N�g�𐶐����� (Create Texture object)
	CreateWICTextureFromFile(Graphics::Get().Device().Get(), L"Asset\\running.png", nullptr, this->texture.GetAddressOf());

	// AnimatedTexture�I�u�W�F�N�g�𐶐����� (Create animated texture object)
	this->animatedTexture = new AnimatedTexture(XMFLOAT2(0.0f, 0.0f), 0.0f, 1.0f, 0.5f);
	// �A�j���[�V�����e�N�X�`�������[�h���� (Load animated texture)
	this->animatedTexture->Load(this->texture.Get(), 3, 10);
}

// Running�N���X�̃C���X�^���X���擾���� (Get instance of Running class)
IState* Running::GetInstance() {
	if (state == nullptr) {
		// Running�I�u�W�F�N�𐶐����� (Create Running object)
		state = new Running();
	}
	return state;
}

// Running�I�u�W�F�N�g�����s���� (Execute Running object)
inline void Running::Execute(const StepTimer& timer) {
	// �A�j���[�V�����X�v���C�g���X�V���� (Update animated sprite)
	this->animatedTexture->Update((float)timer.GetElapsedSeconds());
	// �u�X�y�[�X�v�L�[�������������ꍇ (In case of pussing down space key)
	if (Input::Get()->KeyboardStateTracker()->IsKeyPressed(Keyboard::Keys::Space)) {
		// ���x��0���傫���ꍇ (In case of velocity(vx) > 0)
		if (this->player->VX() > 0) {
			// ���x(vx)�ɏ����l��ݒ肷�� (Assign initial velocity(vx)) 
			this->player->VX(JUMP_SPEED_X);
		} 
		// ���x��0���傫���ꍇ (In case of velocity(vx) < 0)
		else if (this->player->VX() < 0) {
			// ���x(vx)�ɏ����l��ݒ肷�� (Assign initial velocity(vx))
			this->player->VX(-JUMP_SPEED_X);
		}
		// ���x(vy)�ɏ����l��ݒ肷�� (Assign initial velocity(vy))
		this->player->VY(-JUMP_SPEED_Y);
		// �v���C���̏�Ԃ��u��ԁv�ɕύX���� (Change jump state to current state)
		this->player->ChangeState(Jumping::GetInstance());
	}
	// �u���v�L�[�܂��́u���v�L�[����������ꍇ (In case of releasing right and left key)
	if (Input::Get()->KeyboardStateTracker()->IsKeyReleased(Keyboard::Keys::Right) ||
		Input::Get()->KeyboardStateTracker()->IsKeyReleased(Keyboard::Keys::Left)) {
		// �v���C���̏�Ԃ��u�����v�ɕύX���� (Change stand state to current state)
		this->player->ChangeState(Standing::GetInstance());
		// �Î~���� (Assign zero to velociy(vx))
		this->player->VX(0.0);
	}
	// �ʒu�ɑ��x�����Z���� (Add velocity(vx) to position)
	this->player->X(this->player->X() + this->player->VX());
}

// Running�I�u�W�F�N�g��`�悷�� (Render Running object)
inline void Running::Render(SpriteBatch* spriteBatch) {
	// �A�j���[�V�����e�N�X�`����`�悷�� (Render animated texture)
	this->animatedTexture->Draw(spriteBatch, Vector2(this->player->X(), this->player->Y()), player->VX());
}

// Running�I�u�W�F�N�g��j������ (Delete Running object)
void Running::Dispose() {	
	if (state != nullptr) {
		// Running�I�u�W�F�N�g��j������ (Delete Running object)
		delete state;
		state = nullptr;
	}
}

// �f�X�g���N�^ (Destructor)
Running::~Running() {
	if (this->animatedTexture != nullptr)
		// AnimationTexure�I�u�W�F�N�g��j������
		delete this->animatedTexture;
	this->animatedTexture = nullptr;
}
