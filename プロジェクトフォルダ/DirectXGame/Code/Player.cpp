#include <cassert>
#include "Player.h"

using namespace KamataEngine;

void Player::Initialize(KamataEngine::Model* model, const KamataEngine::Vector3& position) {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録
	model_ = model;
	worldTransfrom_.translation_ = position;

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
