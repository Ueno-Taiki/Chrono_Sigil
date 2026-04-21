#pragma once
#include "KamataEngine.h"

enum class AttackType {
	Normal,
	Skill
};

class UI;

// プレイヤーの処理するクラス
class Player {
public:
	~Player();

	// 初期化
	void Initialize(KamataEngine::Model* model, const KamataEngine::Vector3& position);

	// 更新
	void Update();

	// 描画
	void Draw(KamataEngine::Camera& camera);

	// ライフ描画
	void LifeDraw();

	// 攻撃
	void Attack();

	// 通常攻撃の判定
	void NormalAttackHit();

	// スキル攻撃の判定
	void SkillAttackHit();

	// 攻撃受ける
	void Hit(int damage);

	// 攻撃のsetter
	void SetAttackType(AttackType type) { attackType_ = type; }

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

	// テクスチャハンドル
	uint32_t textureHandle_[2];

	// スプライト
	KamataEngine::Sprite* sprite_[2];

	// 攻撃の種類
	AttackType attackType_ = AttackType::Normal;

	// ライフ
	float playerLife = 5.0f;

	// デスフラグ
	bool isDead_ = false;
};

