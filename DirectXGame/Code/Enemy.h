#pragma once
#include "KamataEngine.h"

// 敵を処理するクラス
class Enemy {
public:
	// 初期化
	void Initialize(KamataEngine::Model* model, const KamataEngine::Vector3& position);

	// 更新
	void Update();

	// 描画
	void Draw(KamataEngine::Camera& camera);

	//攻撃受ける
	void Hit(int damage);

	// デスフラグのgetter
	bool isDead() const { return isDead_; }

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransfrom_;
	// モデル
	KamataEngine::Model* model_ = nullptr;

	// 敵のライフ
	float enemyLife = 5.0f;

	// デスフラグ
	bool isDead_ = false;
};
