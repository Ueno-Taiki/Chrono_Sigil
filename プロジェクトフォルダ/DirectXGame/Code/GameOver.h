#pragma once
#include "KamataEngine.h"

// ゲームオーバーの処理
class GameOver {
public:
	~GameOver();

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
	uint32_t textureHandle_ = 0;

	// スプライト
	KamataEngine::Sprite* sprite_ = nullptr;

	//サウンドデータハンドル
	uint32_t Gameover = 0;

	//音声再生ハンドル
	uint32_t voiceHandle_ = 0;
};
