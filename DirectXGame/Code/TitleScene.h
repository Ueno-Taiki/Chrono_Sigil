#pragma once
#include "KamataEngine.h"

class TitleScene {
public:
	~TitleScene();

	void Initialize();

	void Update();

	void Draw();

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	//ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransfrom_;
	
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//スプライト
	KamataEngine::Sprite* sprite_ = nullptr;
};