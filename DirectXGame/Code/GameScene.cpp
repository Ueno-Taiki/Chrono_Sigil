#include "GameScene.h"

using namespace KamataEngine;

GameScene::~GameScene() {
	// 解放処理
	delete modelPlayer_;
}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// 3Dモデルデータの生成
	modelPlayer_ = Model::CreateFromOBJ("player", true);

	// ファイル名を指定してテクスチャを読み込む


	// プレイヤーの生成
	player_ = new Player();
	// プレイヤーの座標
	Vector3 positon = { -18, 0, -20 };
	// プレイヤーの初期化
	player_->Initialize(modelPlayer_, positon);

	// スプライトの生成


	// カメラの初期化
	camera_.Initialize();

	// ワールド変数の初期化
	worldTransfrom_.Initialize();
}

void GameScene::Update() {
	// プレイヤー更新
	player_->Update();

	// 行列を更新
	worldTransfrom_.UpdateMatrix();
}

void GameScene::Draw() {
	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	// ここに2Dスプライトの描画処理を記述する


	// スプライト描画後処理
	Sprite::PostDraw();

	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
	// 3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	// ここに3Dモデルインスタンスの描画処理を記述する
	player_->Draw(camera_);


	// 3Dモデル描画後処理
	Model::PostDraw();

	// スプライト描画後処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	// ここに2Dスプライトの描画処理を記述する


	// スプライト描画後処理
	Sprite::PostDraw();
}
