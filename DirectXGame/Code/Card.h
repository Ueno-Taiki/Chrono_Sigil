#pragma once
#include "KamataEngine.h"

class Card {
public:
	~Card();

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
	uint32_t textureHandle_[5];

	// スプライト
	KamataEngine::Sprite* sprite_[5];

	// カードの枚数
	static inline const int MAX = 5;
};

