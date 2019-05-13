
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

	// コンストラクタ
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
	// テクスチャをロードする
	void Load(ID3D11ShaderResourceView* texture, int frameCount, int framesPerSecond){
		if (frameCount < 0 || framesPerSecond <= 0)
			throw std::invalid_argument("AnimatedTexture");

		// フレームを初期化する
		this->frame = 0;
		// フレームカウントを設定する
		this->frameCount = frameCount;
		// フレームを描画する時間
		this->timePerFrame = 1.0f / float(framesPerSecond);
		// 総経過時間を初期化する
		this->totalElapsed = 0.0f;
		// textureのポインタをtextureメンバ変数に設定する
		this->texture = texture;

		if (texture){
			// Resourceインターフェース
			Microsoft::WRL::ComPtr<ID3D11Resource> resource;
			// Textureインターフェースを取得する
			texture->GetResource(resource.GetAddressOf());

			D3D11_RESOURCE_DIMENSION dim;
			// リソースタイプを取得する
			resource->GetType(&dim);

			// Texture2D内部データにアクセスするためのインターフェース
			Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
			resource.As(&texture2D);
			// TEXTURE_2D_DESCに対するインターフェース
			D3D11_TEXTURE2D_DESC desc;
			// 2Dテクスチャの記述内容を取得する
			texture2D->GetDesc(&desc);
			// テクスチャ幅を取得する
			this->textureWidth = int(desc.Width);
			// テクスチャ高を取得する
			this->textureHeight = int(desc.Height);
		}
	}

	// アニメーションを更新する
	void Update(float elapsed) {
		// 経過時間を総経過時間に加算する
		this->totalElapsed += elapsed;
		// 総経過時間がフレームを描画する時間を超えた場合
		if (this->totalElapsed > this->timePerFrame) {
			// フレームを1増やす
			++this->frame;
			// フレームをフレームカウントで割った余りをフレームに設定する
			this->frame = this->frame % this->frameCount;
			// 総経過時間からフレームを描画する時間を減らす
			this->totalElapsed -= this->timePerFrame;
		}
	}

	// アニメーションを描画する
	void Draw(DirectX::SpriteBatch* spriteBatch, const Vector2& position, float vx) const {
		// 指定されたフレームのテクスチャを描画する
		Draw(spriteBatch, this->frame, position, vx);
	}

	// アニメーションを描画する
	void Draw(DirectX::SpriteBatch* spriteBatch, int frame, const Vector2& position, float vx) const {
		// フレーム幅を算出する
		int frameWidth = this->textureWidth / this->frameCount;
		// 原点を設定する
		Vector2 origin = Vector2((float)frameWidth / 2.0f, (float)this->textureHeight / 2.0f);
		// ソース矩形を設定する
		RECT sourceRectangle;
		// 左
		sourceRectangle.left = frameWidth * frame;
		// 上
		sourceRectangle.top = 0;
		// 右
		sourceRectangle.right = sourceRectangle.left + frameWidth;
		// 下
		sourceRectangle.bottom = this->textureHeight;
		// スプライトの効果を設定しない
		DirectX::SpriteEffects effects = DirectX::SpriteEffects_None;
		// 後向きかどうか 
		if (vx < 0.0f) {
			// テクスチャを反転する
			effects = DirectX::SpriteEffects_FlipHorizontally;
		}
		// テクスチャを描画する
		spriteBatch->Draw(this->texture, position, &sourceRectangle, Colors::White, rotation, origin, scale, effects, this->depth);
	}

private:

	// フレーム
	int  frame;
	// フレームカウント
	int  frameCount;
	// テクスチャ幅
	int  textureWidth;
	// テクスチャ高
	int  textureHeight;
	// フレームに対する時間
	float timePerFrame;
	// 総経過時間
	float totalElapsed;
	// 深度
	float depth;
	// ローテーション
	float rotation;
	// 中心座標
	Vector2 origin;
	// スケール
	Vector2 scale;
	// テクスチャ
	//Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>  texture;
	ID3D11ShaderResourceView* texture;
};

#endif // ANIMATED_TEXTURE_DEFINED
