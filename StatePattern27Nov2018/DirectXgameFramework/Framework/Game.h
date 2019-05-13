/*
@brief		�Q�[��
@file		Game.h
@date		2018/11/27
@author		Shozo Tanaka
*/

#pragma once
#ifndef GAME_DEFINED
#define GAME_DEFINED

// Use the C++ standard templated min/max
#define NOMINMAX

#include <windows.h>
#include <iostream>
#include <string>
#include <iomanip>

#include <d3d11.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <Effects.h>
#include <Model.h>
#include <Keyboard.h>
#include <GeometricPrimitive.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <algorithm>

#include "..\\Framework\\StepTimer.h"
#include "..\\Framework\\dx.h"
#include "..\\Framework\\Window.h"
#include "..\\Framework\\Graphics.h"

#include "..\\Game\\Scene.h"
#include "..\\Game\\TitleScene.h"


using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace DX;
using namespace std;

class Window;

// �Q�[������������ 
class Game {
public:
	// �R���X�g���N�^ (Constructor)
    Game(int width, int height);
    // �Q�[���ɕK�v�ȃI�u�W�F�N�g���������� (Initialize game object)
    void Initialize();
    // ��{�Q�[�����[�v�����s���� (Run basic game loop)
	MSG Run();
	// �I�������������Ȃ� (Finalize game)
	void Finalize();

    // ���b�Z�[�W (Messages)
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // �v���p�e�B (Properties)
    void GetDefaultSize(int& width, int& height) const;

private:
	// �Q�[�����X�V���� (Update game)
    void Update(const StepTimer& timer);
    // �V�[����`�悷�� (Render scene)
	void Render();
	// �o�b�N�o�b�t�@���N���A���� (Clear back buffer)
    void Clear();
	// �o�b�N�o�b�t�@���X�N���[���ɑ���
    void Present();
	// FPS��`�悷�� (Draw FPS)
	void DrawFPS();

private:
	// �C���X�^���X�n���h�� Instance handle
	HINSTANCE hInstance;
	// ���s���̃E�B���h�E�̕\�����@ Initial state of main window 
	int nCmdShow;
    // �E�B���h�E�n���h�� Windows handle
    HWND hWnd;
	// �E�B���h�E�� Window width
    int width;
	// �E�B���h�E�� Window height
    int height;

	// �E�B���h�E Window
	unique_ptr<Window> window;
	// DirectX�O���t�B�b�N�X DirectX Graphics
	unique_ptr<Graphics> graphics;
	// �@�\���x�� Feature level
    D3D_FEATURE_LEVEL featureLevel;
    // ���[�v�^�C�}�[ Loop timer
    StepTimer timer;

	// �X�v���C�g�o�b�` SpriteBatch
	unique_ptr<SpriteBatch>	spriteBatch;
	// �t�H���g Font
	unique_ptr<SpriteFont> font;

	// �G�t�F�N�g�t�@�N�g���C���^�[�t�F�[�X IEffectFactory
	unique_ptr<IEffectFactory> fxFactory;
	// �R�����X�e�[�g CommonStates
	unique_ptr<CommonStates> commonStates;

	// ���݂̃V�[�� current scene
	Scene* currentScene;
};

#endif	// GAME
