/*
@brief		�L�[�{�[�h����
@file		Input.h
@date		2018/11/25
@author		Shozo Tanaka
*/

#pragma once
#ifndef INPUT_DEFINED
#define INPUT_DEFINED

#include <memory.h>
#include <windows.h>
#include <Keyboard.h>

class Input {
public:
	// Keyboard�I�u�W�F�N�g�ւ̃|�C���^���擾����
	DirectX::Keyboard* Keyboard() {
		return this->keyboard.get();
	}
	// KeyboardStateTracker�I�u�W�F�N�g�ւ̃|�C���^���擾����
	DirectX::Keyboard::KeyboardStateTracker* KeyboardStateTracker() {
		return this->keyboardStateTracker.get();
	}
	// KeyboardState���擾����
	DirectX::Keyboard::State KeyboardState() {
		return this->keyboardState;
	}

	// Input�I�u�W�F�N�g�ւ̃|�C���^���擾����
	static Input* Get() {
		if (input == nullptr) {
			// Input�I�u�W�F�N�g�𐶐�����
			input.reset(new Input());
		}
		return input.get();
	}

	// ����������
	void Initialize() {
		// Keyboard�I�u�W�F�N�g�𐶐�����
		this->keyboard = std::make_unique<DirectX::Keyboard>();
		// KeyboardStateTracker�I�u�W�F�N�g�𐶐�����
		this->keyboardStateTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	}

	// �X�V����
	void Update() {
		// �L�[�{�[�h�̏�Ԃ��擾����
		this->keyboardState = keyboard->GetState();
		// �L�[�{�[�h�g���b�J�[���X�V����
		this->keyboardStateTracker->Update(keyboardState);
	}

	// �㏈���������Ȃ�
	void Finalize() {
		// Keyboard�I�u�W�F�N�g�����Z�b�g����
		this->keyboard.reset();
		// KeyboardStateTracker�I�u�W�F�N�g�����Z�b�g����
		this->keyboardStateTracker.reset();
	}
private:
	// �R���X�g���N�^
	Input(){}
	static std::unique_ptr<Input> input;
	// �L�[�{�[�h�I�u�W�F�N�g�ւ̃|�C���^
	std::unique_ptr<DirectX::Keyboard> keyboard;
	// �L�[�{�[�h�X�e�[�g�g���b�J�[�I�u�W�F�N�g�ւ̃|�C���^
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> keyboardStateTracker;
	// �L�[�{�[�h�X�e�[�g
	DirectX::Keyboard::State keyboardState;
};

#endif	// INPUT_DEFINED


