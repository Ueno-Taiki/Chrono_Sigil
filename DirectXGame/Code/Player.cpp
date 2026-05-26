#include <cassert>
#include "Player.h"

using namespace KamataEngine;

Player::~Player() { 
	for (int i = 0; i < 2; i++) {
		delete sprite_[i];
	}
}

void Player::Initialize(KamataEngine::Model* model, const KamataEngine::Vector3& position) {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録
	model_ = model;
	worldTransfrom_.translation_ = position;

	// ファイルを指定してテクスチャを読み込む
	textureHandle_[0] = TextureManager::Load("UI/Life1.png");
	textureHandle_[1] = TextureManager::Load("UI/Life2.png");

	// スプライト
	sprite_[0] = Sprite::Create(textureHandle_[0], { 70, 300 });
	sprite_[1] = Sprite::Create(textureHandle_[1], { 78, 308 });

	// 基底クラス呼ぶ
	Character::Initialize(model, position);

	// ワールト座標の初期化
	worldTransfrom_.Initialize();
}

void Player::Update() { 
	// 行列を更新
	worldTransfrom_.UpdateMatrix();
}

void Player::Draw(KamataEngine::Camera& camera) {
	// 3Dモデルを描画
	model_->Draw(worldTransfrom_, camera);
}

void Player::LifeDraw() {
	if (playerLife_ == 5) {
		sprite_[0]->Draw();
		sprite_[1]->Draw();
	}
	if (playerLife_ == 4) {
		sprite_[0]->Draw();

	}
	if (playerLife_ == 3) {
		sprite_[0]->Draw();

	}
	if (playerLife_ == 2) {
		sprite_[0]->Draw();

	}
	if (playerLife_ == 1) {
		sprite_[0]->Draw();

	}
	if (playerLife_ == 0) {
		sprite_[0]->Draw();

	}
}

// 攻撃
void Player::Attack() { 
	switch (attackType_) {
		case AttackType::Normal:
		NormalAttackHit();
		break;

		case AttackType::Skill:
		SkillAttackHit();
		break;
	}
}

// 通常攻撃の判定
void Player::NormalAttackHit() { }

// スキル攻撃の判定
void Player::SkillAttackHit() { }



