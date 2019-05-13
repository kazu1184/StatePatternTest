/*
@brief		キーボード入力
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
	// Keyboardオブジェクトへのポインタを取得する
	DirectX::Keyboard* Keyboard() {
		return this->keyboard.get();
	}
	// KeyboardStateTrackerオブジェクトへのポインタを取得する
	DirectX::Keyboard::KeyboardStateTracker* KeyboardStateTracker() {
		return this->keyboardStateTracker.get();
	}
	// KeyboardStateを取得する
	DirectX::Keyboard::State KeyboardState() {
		return this->keyboardState;
	}

	// Inputオブジェクトへのポインタを取得する
	static Input* Get() {
		if (input == nullptr) {
			// Inputオブジェクトを生成する
			input.reset(new Input());
		}
		return input.get();
	}

	// 初期化する
	void Initialize() {
		// Keyboardオブジェクトを生成する
		this->keyboard = std::make_unique<DirectX::Keyboard>();
		// KeyboardStateTrackerオブジェクトを生成する
		this->keyboardStateTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	}

	// 更新する
	void Update() {
		// キーボードの状態を取得する
		this->keyboardState = keyboard->GetState();
		// キーボードトラッカーを更新する
		this->keyboardStateTracker->Update(keyboardState);
	}

	// 後処理をおこなう
	void Finalize() {
		// Keyboardオブジェクトをリセットする
		this->keyboard.reset();
		// KeyboardStateTrackerオブジェクトをリセットする
		this->keyboardStateTracker.reset();
	}
private:
	// コンストラクタ
	Input(){}
	static std::unique_ptr<Input> input;
	// キーボードオブジェクトへのポインタ
	std::unique_ptr<DirectX::Keyboard> keyboard;
	// キーボードステートトラッカーオブジェクトへのポインタ
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> keyboardStateTracker;
	// キーボードステート
	DirectX::Keyboard::State keyboardState;
};

#endif	// INPUT_DEFINED


