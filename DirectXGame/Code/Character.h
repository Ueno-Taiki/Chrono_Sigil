#pragma once
#include "KamataEngine.h"

class Character {
public:
	virtual ~Character() = default;

	// 共通処理
	virtual void Initialize(KamataEngine::Model* model,const KamataEngine::Vector3& position);

	virtual void Update() = 0;
	virtual void Draw(KamataEngine::Camera& camera);
	virtual void LifeDraw() = 0;

	virtual void Hit(int damage);

	//--------------------------------
	// Getter
	//--------------------------------

	bool IsDead() const { return isDead_; }

	float GetLife() const { return life_; }

	//--------------------------------
	// Setter
	//--------------------------------

	void SetLife(float life) { life_ = life; }

protected:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

	// モデル
	KamataEngine::Model* model_ = nullptr;

	// ライフ
	float life_ = 5.0f;

	// デスフラグ
	bool isDead_ = false;

	// テクスチャ
	uint32_t textureHandle_[2];

	// スプライト
	KamataEngine::Sprite* sprite_[2];
};

