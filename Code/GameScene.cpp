#include "GameScene.h"

using namespace KamataEngine;

GameScene::~GameScene() {
	// 解放処理
	delete modelPlayer_;
	delete modelEnemy_;
	delete modelSkydome_;
	// 音声停止
	audio_->StopWave(voiceHandle_);
}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// 3Dモデルデータの生成
	modelPlayer_ = Model::CreateFromOBJ("player", true);
	modelEnemy_ = Model::CreateFromOBJ("enemy", true);
	modelSkydome_ = Model::CreateFromOBJ("SkyDome", true);

	// BGM・SE読み込み
	BGM = audio_->LoadWave("BGM/BGM.wav");

	// プレイヤーの生成
	player_ = new Player();
	// プレイヤーの座標
	Vector3 playerPositon = { -18, 0, -20 };
	// プレイヤーの初期化
	player_->Initialize(modelPlayer_, playerPositon);

	// 敵の生成
	enemy_ = new Enemy();
	// 敵の座標
	Vector3 enemyPositon = { 15, 0, -20 };
	// 駅の初期化
	enemy_->Initialize(modelEnemy_, enemyPositon);

	// 天球の生成
	skydome_ = new Skydome();
	// 天球の初期化
	skydome_->Initialize(modelSkydome_);

	// カメラの初期化
	camera_.farZ = 600;
	camera_.Initialize();

	// 音声再生
	voiceHandle_ = audio_->PlayWave(BGM, true);

	// ワールド変数の初期化
	worldTransfrom_.Initialize();
}

void GameScene::Update() {
	// プレイヤー更新
	player_->Update();

	// 敵更新
	enemy_->Update();

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

	// プレイヤー描画
	player_->Draw(camera_);

	// 敵描画
	enemy_->Draw(camera_);

	// 天球描画
	skydome_->Draw(camera_);

	// 3Dモデル描画後処理
	Model::PostDraw();

	// スプライト描画後処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	// ここに2Dスプライトの描画処理を記述する


	// スプライト描画後処理
	Sprite::PostDraw();
}
