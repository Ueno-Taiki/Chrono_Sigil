#pragma once
#include "KamataEngine.h"
#include "Character.h"

// 敵を処理するクラス
class Enemy : public Character {
public:
	~Enemy();

	// 初期化
	void Initialize(KamataEngine::Model* model,const KamataEngine::Vector3& position) override;

	// 更新
	void Update() override;

	// 描画
	void Draw(KamataEngine::Camera& camera) override;

	// ライフ描画
	void LifeDraw() override;

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransfrom_;
	// モデル
	KamataEngine::Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_[2];

	// スプライト
	KamataEngine::Sprite* sprite_[2];

	// 敵のライフ
	float enemyLife_ = 5.0f;

	// デスフラグ
	bool isDead_ = false;
};
