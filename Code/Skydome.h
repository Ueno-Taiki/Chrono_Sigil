#pragma once
#include "KamataEngine.h"

class Skydome {
public:
	// 初期化
	void Initialize(KamataEngine::Model* model);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(KamataEngine::Camera& camera);

private:  
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransfrom_;
	// モデル
	KamataEngine::Model* model_ = nullptr;
};
