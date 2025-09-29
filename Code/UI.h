#pragma once
#include "KamataEngine.h"

class UI{
public:
	~UI();

	void Initialize();

	void Update();

	void Draw();

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransfrom_;

	// テクスチャハンドル
	uint32_t textureHandle_[3];

	// 数字用スプライト
	KamataEngine::Sprite* sprite_ = nullptr;

	// 星用スプライト
	KamataEngine::Sprite* spriteStar_[5];

	// SP
	int sp = 3;

	// 文字のサイズ
	KamataEngine::Vector2 size = { 32.0f, 64.0f };
};