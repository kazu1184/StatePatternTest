/*
@brief		グラフィックス
@file		Graphics.h
@date		2018/11/25
@author		Shozo Tanaka
*/

#pragma once
#ifndef GRAPHICS_DEFINED
#define GRAPHICS_DEFINED

#include <windows.h>
#include <wrl/client.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

#include <algorithm>
#include <exception>
#include <memory>
#include <stdexcept>
#include <SimpleMath.h>
#include <wrl.h>
#include "dx.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace std;

// Uncopyableクラス
class Uncopyable {
protected:
	Uncopyable() = default;
	~Uncopyable() = default;
private:
	Uncopyable(const Uncopyable&) = delete;
	Uncopyable& operator =(const Uncopyable&) = delete;
};

// Graphicsクラス
class Graphics : private Uncopyable {
private:
	// コンストラクタ (Constructor)
	Graphics() {}

public:
	// Graphicsクラスのインスタンスを取得する (Get instance of Graphics class)
	static Graphics& Get() {
		if (graphics.get() == nullptr) {
			graphics.reset(new Graphics());
		}
		return *graphics.get();
	}
	// Graphicsオブジェクトをリセットする (Dispose Graphics object)
	static void Dispose() {
		graphics.reset();
	}
	// ウィンドウハンドルを取得する (Get hWnd)
	HWND HWnd() {
		return hWnd;
	}
	// ウィンドウハンドルを設定する (Set hWnd)
	void HWnd(HWND hWnd) {
		this->hWnd = hWnd;
	}
	// ウィンドウ幅を取得する (Get window width)
	int Width() {
		return width;
	}
	// ウィンドウ幅を設定する (Set window width)
	void Width(int width) {
		this->width = width;
	}
	// ウィンドウ高を取得する (Get window height)
	int Height() {
		return height;
	}
	// ウィンドウ高を設定する (Set window height)
	void Height(int height) {
		this->height = height;
	}
	// デバイスを取得する (Get device object)
	Microsoft::WRL::ComPtr<ID3D11Device> Device() {
		return this->device; 
	}
	// デバイスを設定する (Set device object)
	void Device(Microsoft::WRL::ComPtr<ID3D11Device> device) {
		this->device = device;
	}
	// デバイスコンテキストを取得する (Get device context object)
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> Context() {
		return this->context;
	}
	// デバイスコンテキストを設定する (Set device context object)
	void Context(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context) {
		this->context = context;
	}

	// スワップチェインを取得する (Get SwapChain)
	Microsoft::WRL::ComPtr<IDXGISwapChain> SwapChain() {
		return swapChain;
	}
	// スワップチェインを設定する (Set SwapChain)
	void SwapChain(Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain) {
		this->swapChain = swapChain;
	}
	// レンダーターゲットビューを取得する (Get RenderTargetView)
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> RenderTargetView() {
		return renderTargetView;
	}
	// レンダーターゲットビューを設定する (Set RenderTargetView)
	void RenderTargetView(Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView) {
		this->renderTargetView = renderTargetView;
	}

	// デプスステンシルビューを取得する (Get DepthStencilView)
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> DepthStencilView() {
		return depthStencilView;
	}
	// デプスステンシルビューを設定する (Set DepthStencilView)
	void DepthStencilView(Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView) {
		this->depthStencilView = depthStencilView;
	}

	// デバイスを生成する (Create device)
	void CreateDevice();

	// リソースを生成する (Create Resource)
	void CreateResources();

	// デバイスロストが発生した場合 (OnDeviceLost)
	void OnDeviceLost();

private:
	static std::unique_ptr<Graphics> graphics;

	HWND hWnd;
	int  width;
	int  height;
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11Device1> device1;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>	context;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1> context1;
	D3D_FEATURE_LEVEL  featureLevel;

	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain1;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;
};

#endif	// GRAPHICS_DEFINED

