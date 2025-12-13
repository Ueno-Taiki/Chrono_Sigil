#include <cassert>
#include "Enemy.h"

using namespace KamataEngine;

void Enemy::Initialize(KamataEngine::Model* model, const KamataEngine::Vector3& position) {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// NULLポインタチャック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録
	model_ = model;
	worldTransfrom_.translation_ = position;

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