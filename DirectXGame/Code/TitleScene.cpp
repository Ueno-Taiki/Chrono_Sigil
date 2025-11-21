#include "TitleScene.h"
#include <cassert>

using namespace KamataEngine;

TitleScene::~TitleScene() { 
	delete sprite_;
	// 音声停止
	audio_->StopWave(voiceHandle_);
}

void TitleScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ワールド変数の初期化
	worldTransfrom_.Initialize();
	worldTransfrom_.scale_ = {2, 2, 2};

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("Title.png");

	// BGM・SE読み込み
	GameStart = audio_->LoadWave("BGM/GameStart.wav");

	// スプライトの生成
	sprite_ = Sprite::Create(textureHandle_, {0, 0});

	// 音声再生
	voiceHandle_ = audio_->PlayWave(GameStart, true);
}

void TitleScene::Update() {
}

void TitleScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);
	sprite_->Draw();
	// プライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
}

