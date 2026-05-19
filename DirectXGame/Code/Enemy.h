#pragma once
#include "KamataEngine.h"

// 敵を処理するクラス
class Enemy {
public:
	~Enemy();

	// 初期化
	void Initialize(KamataEngine::Model* model, const KamataEngine::Vector3& position);

	// 更新
	void Update();

	// 描画
	void Draw(KamataEngine::Camera& camera);

	// ライフ描画
	void LifeDraw();

	//攻撃受ける
	void Hit(int damage);

	//========================
	// Getter
	//========================

	// デスフラグのgetter
	bool isDead() const { return isDead_; }

	// ライフ取得
	float GetLife() const { return enemyLife_; }

	//========================
	// Setter
	//========================

	// ライフ設定
	void SetLife(float life);

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
