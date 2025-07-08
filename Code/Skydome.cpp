#include "Skydome.h"
#include <cassert>

void Skydome::Initialize(KamataEngine::Model* model) {
	// NULLポインタをチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	
	// ワールド変数の初期化
	worldTransfrom_.Initialize();
}

void Skydome::Update() {}

void Skydome::Draw(KamataEngine::Camera& camera) {
	//3Dモデル描画
	model_->Draw(worldTransfrom_, camera);
}
