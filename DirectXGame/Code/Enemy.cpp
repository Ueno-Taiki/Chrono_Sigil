#include <cassert>
#include "Enemy.h"

using namespace KamataEngine;

Enemy::~Enemy() {
	for (int i = 0; i < 2; i++) {
		delete sprite_[i];
	}
}

void Enemy::Initialize(KamataEngine::Model* model, const KamataEngine::Vector3& position) {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// NULLポインタチャック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録
	model_ = model;
	worldTransfrom_.translation_ = position;

	// ファイルを指定してテクスチャを読み込む
	textureHandle_[0] = TextureManager::Load("UI/Life1.png");
	textureHandle_[1] = TextureManager::Load("UI/Life2.png");

	// スプライト
	sprite_[0] = Sprite::Create(textureHandle_[0], { 1020, 80 });
	sprite_[1] = Sprite::Create(textureHandle_[1], { 1028, 88 });

	// ワールト座標の初期化
	worldTransfrom_.Initialize();
}

void Enemy::Update() {
	// 行列計算
	worldTransfrom_.UpdateMatrix();
}

void Enemy::Draw(KamataEngine::Camera& camera) {
	// 3Dモデルを描画
	model_->Draw(worldTransfrom_, camera);
}

// ライフ描画
void Enemy::LifeDraw() {
	if (enemyLife == 5) {
		sprite_[0]->Draw();
		sprite_[1]->Draw();
	}
	if (enemyLife == 4) {
		sprite_[0]->Draw();

	}
	if (enemyLife == 3) {
		sprite_[0]->Draw();

	}
	if (enemyLife == 2) {
		sprite_[0]->Draw();

	}
	if (enemyLife == 1) {
		sprite_[0]->Draw();

	}
	if (enemyLife == 0) {
		sprite_[0]->Draw();

	}
}

// 攻撃を受ける
void Enemy::Hit(int damage) {
	enemyLife = (enemyLife - damage);

	// ライフが0の時死ぬ
	if (enemyLife == 0) {
		isDead_ = true;
	}
}