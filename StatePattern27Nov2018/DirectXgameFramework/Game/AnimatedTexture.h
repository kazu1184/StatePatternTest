
//--------------------------------------------------------------------------------------
// File: AnimatedTexture.h
//
// C++ version of the C# example on how to animate a 2D sprite using SpriteBatch
// http://msdn.microsoft.com/en-us/library/bb203866.aspx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
// @date	2018/11/25	
// @author	Modified by Shozo Tanaka

#pragma once
#ifndef ANIMATED_TEXTURE_DEFINED
#define ANIMATED_TEXTURE_DEFINED
#include <windows.h>
#include <wrl/client.h>
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <DirectXColors.h>
#include <WICTextureLoader.h>
#include <algorithm>
#include <Memory>
#include <stdexcept>
#include <SpriteBatch.h>
#include "..\\Game\\Player.h"

class AnimatedTexture {
public:

	// �R���X�g���N�^
	AnimatedTexture(const Vector2& origin, float rotation, float scale, float depth) :
		frame(0),
		frameCount(0),
		textureWidth(0),
		textureHeight(0),
		timePerFrame(0.0f),
		totalElapsed(0.0f),
		origin(origin),
		rotation(rotation),
		scale(scale),
		depth(depth){
	}
	// �e�N�X�`�������[�h����
	void Load(ID3D11ShaderResourceView* texture, int frameCount, int framesPerSecond){
		if (frameCount < 0 || framesPerSecond <= 0)
			throw std::invalid_argument("AnimatedTexture");

		// �t���[��������������
		this->frame = 0;
		// �t���[���J�E���g��ݒ肷��
		this->frameCount = frameCount;
		// �t���[����`�悷�鎞��
		this->timePerFrame = 1.0f / float(framesPerSecond);
		// ���o�ߎ��Ԃ�����������
		this->totalElapsed = 0.0f;
		// texture�̃|�C���^��texture�����o�ϐ��ɐݒ肷��
		this->texture = texture;

		if (texture){
			// Resource�C���^�[�t�F�[�X
			Microsoft::WRL::ComPtr<ID3D11Resource> resource;
			// Texture�C���^�[�t�F�[�X���擾����
			texture->GetResource(resource.GetAddressOf());

			D3D11_RESOURCE_DIMENSION dim;
			// ���\�[�X�^�C�v���擾����
			resource->GetType(&dim);

			// Texture2D�����f�[�^�ɃA�N�Z�X���邽�߂̃C���^�[�t�F�[�X
			Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
			resource.As(&texture2D);
			// TEXTURE_2D_DESC�ɑ΂���C���^�[�t�F�[�X
			D3D11_TEXTURE2D_DESC desc;
			// 2D�e�N�X�`���̋L�q���e���擾����
			texture2D->GetDesc(&desc);
			// �e�N�X�`�������擾����
			this->textureWidth = int(desc.Width);
			// �e�N�X�`�������擾����
			this->textureHeight = int(desc.Height);
		}
	}

	// �A�j���[�V�������X�V����
	void Update(float elapsed) {
		// �o�ߎ��Ԃ𑍌o�ߎ��Ԃɉ��Z����
		this->totalElapsed += elapsed;
		// ���o�ߎ��Ԃ��t���[����`�悷�鎞�Ԃ𒴂����ꍇ
		if (this->totalElapsed > this->timePerFrame) {
			// �t���[����1���₷
			++this->frame;
			// �t���[�����t���[���J�E���g�Ŋ������]����t���[���ɐݒ肷��
			this->frame = this->frame % this->frameCount;
			// ���o�ߎ��Ԃ���t���[����`�悷�鎞�Ԃ����炷
			this->totalElapsed -= this->timePerFrame;
		}
	}

	// �A�j���[�V������`�悷��
	void Draw(DirectX::SpriteBatch* spriteBatch, const Vector2& position, float vx) const {
		// �w�肳�ꂽ�t���[���̃e�N�X�`����`�悷��
		Draw(spriteBatch, this->frame, position, vx);
	}

	// �A�j���[�V������`�悷��
	void Draw(DirectX::SpriteBatch* spriteBatch, int frame, const Vector2& position, float vx) const {
		// �t���[�������Z�o����
		int frameWidth = this->textureWidth / this->frameCount;
		// ���_��ݒ肷��
		Vector2 origin = Vector2((float)frameWidth / 2.0f, (float)this->textureHeight / 2.0f);
		// �\�[�X��`��ݒ肷��
		RECT sourceRectangle;
		// ��
		sourceRectangle.left = frameWidth * frame;
		// ��
		sourceRectangle.top = 0;
		// �E
		sourceRectangle.right = sourceRectangle.left + frameWidth;
		// ��
		sourceRectangle.bottom = this->textureHeight;
		// �X�v���C�g�̌��ʂ�ݒ肵�Ȃ�
		DirectX::SpriteEffects effects = DirectX::SpriteEffects_None;
		// ��������ǂ��� 
		if (vx < 0.0f) {
			// �e�N�X�`���𔽓]����
			effects = DirectX::SpriteEffects_FlipHorizontally;
		}
		// �e�N�X�`����`�悷��
		spriteBatch->Draw(this->texture, position, &sourceRectangle, Colors::White, rotation, origin, scale, effects, this->depth);
	}

private:

	// �t���[��
	int  frame;
	// �t���[���J�E���g
	int  frameCount;
	// �e�N�X�`����
	int  textureWidth;
	// �e�N�X�`����
	int  textureHeight;
	// �t���[���ɑ΂��鎞��
	float timePerFrame;
	// ���o�ߎ���
	float totalElapsed;
	// �[�x
	float depth;
	// ���[�e�[�V����
	float rotation;
	// ���S���W
	Vector2 origin;
	// �X�P�[��
	Vector2 scale;
	// �e�N�X�`��
	//Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>  texture;
	ID3D11ShaderResourceView* texture;
};

#endif // ANIMATED_TEXTURE_DEFINED
