#include "GameScene.h"

using namespace KamataEngine;

GameScene::~GameScene() {
	// 音声停止
	audio_->StopWave(voiceHandle_);
}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// 3Dモデルデータの生成
	modelPlayer_.reset(Model::CreateFromOBJ("player", true));
	modelEnemy_.reset(Model::CreateFromOBJ("enemy", true));
	modelSkydome_.reset(Model::CreateFromOBJ("SkyDome", true));

	// BGM・SE読み込み
	BGM = audio_->LoadWave("BGM/BGM.wav");

	// プレイヤーの生成
	auto player = std::make_unique<Player>();
	// プレイヤーの座標
	Vector3 playerPositon = { -18, 0, -20 };
	// プレイヤーの初期化
	player->Initialize(modelPlayer_.get(), playerPositon);
	// ポインタ保持
	player_ = player.get();
	// vectorに追加
	characters_.push_back(std::move(player));

	// 敵の生成
	auto enemy = std::make_unique<Enemy>();
	// 敵の座標
	Vector3 enemyPositon = { 15, 0, -20 };
	// 敵の初期化
	enemy->Initialize(modelEnemy_.get(), enemyPositon);
	// ポインタ保持
	enemy_ = enemy.get();
	// vectorに追加
	characters_.push_back(std::move(enemy));

	// カードの生成
	card_ = std::make_unique<Card>();
	// カードの初期化
	card_->Initialize();

	// UIの生成
	ui_ = std::make_unique<UI>();
	// UIの初期化
	ui_->Initialize();

	// 天球の生成
	skydome_ = std::make_unique<Skydome>();
	// 天球の初期化
	skydome_->Initialize(modelSkydome_.get());

	// カメラの初期化
	camera_.farZ = 600;
	camera_.Initialize();

	// 音声再生
	voiceHandle_ = audio_->PlayWave(BGM, true);

	// ワールド変数の初期化
	worldTransfrom_.Initialize();
}

void GameScene::Update() {
	// キャラクターの更新
	for (auto& character : characters_) {
		character->Update();
	}

	// カード更新
	card_->Update();

	// UI更新
	ui_->Update();

	// UIの選択をPlayerに反映
	player_->SetAttackType(ui_->GetAttackType());

	// 攻撃ボタンが押されたら
	if (input_->TriggerKey(DIK_RETURN)) {
		player_->Attack();
	}

	//プレイヤーが死んだ時
	if (player_->IsDead()) {
		finished_ = true;
	}

	//敵が死んだ時
	if (enemy_->IsDead()) {
		cleared_ = true;
	}

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

	// キャラクター描画
	for (auto& character : characters_) {
		character->Draw(camera_);
	}

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

	// プレイヤーライフ描画
	player_->LifeDraw();

	// 敵のライフ描画
	enemy_->LifeDraw();

	// カード描画
	card_->Draw();

	// UI描画
	ui_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
}
