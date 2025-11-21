#include "Card.h"
#include <cassert>

using namespace KamataEngine;

Card::~Card() { 
	for (int i = 0; i < MAX; i++) {
		delete sprite_[i];
	}
}

void Card::Initialize() { 
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ワールド変数の初期化
	worldTransfrom_.Initialize();
	worldTransfrom_.scale_ = { 2, 2, 2 };

	// ファイル名を指定してテクスチャを読み込む
	for (int i = 0; i < MAX; i++) {
		textureHandle_[i] = TextureManager::Load("Card/Card" + std::to_string(i + 1) + ".png");
	}

	// スプライトの生成
	for (int i = 0; i < MAX; i++) {
		sprite_[i] = Sprite::Create(textureHandle_[i], { 0, 0 });
	}

	// 固定配置
	sprite_[0]->SetPosition({ 0, 600 });
	sprite_[1]->SetPosition({ 80, 600 });
	sprite_[2]->SetPosition({ 160, 600 });
	sprite_[3]->SetPosition({ 240, 600 });
	sprite_[4]->SetPosition({ 320, 600 });
}

void Card::Update() { 
}

void Card::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);
	for (int i = 0; i < MAX; i++) {
		sprite_[i]->Draw();
	}
	// プライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
}

