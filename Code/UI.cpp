#include <cassert>
#include "UI.h"

using namespace KamataEngine;

UI::~UI() { 
	// 数字削除
	delete sprite_;
	// 星削除
	for (int i = 0; i < 5; i++) {
		delete spriteStar_[i];
	}
}

void UI::Initialize() { 
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ワールド変数の初期化
	worldTransfrom_.Initialize();
	worldTransfrom_.scale_ = { 2, 2, 2 };

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_[0] = TextureManager::Load("UI/number.png");
	textureHandle_[1] = TextureManager::Load("UI/Star1.png");
	textureHandle_[2] = TextureManager::Load("UI/Star2.png");

	// 数字用スプライト
	sprite_ = Sprite::Create(textureHandle_[0], { 750, 640 });
	sprite_->SetSize(size);

	// 星を5つ作成して横並びに配置
	for (int i = 0; i < 5; i++) {
		spriteStar_[i] = Sprite::Create(textureHandle_[1], { 800.0f + i * 36.0f, 652.0f });
		spriteStar_[i]->SetSize({ 32.0f, 32.0f });
	}
}

void UI::Update() { 
	// 数字用処理
	int nowNumber = sp % 10;
	sprite_->SetTextureRect({ size.x * nowNumber, 0 }, size);

	// 星の表示を更新
	int starCount = min(sp, 5);
	for (int i = 0; i < 5; i++) {
		if (i < starCount) {
			spriteStar_[i]->SetTextureHandle(textureHandle_[1]); // 塗りつぶし
		}
		else {
			spriteStar_[i]->SetTextureHandle(textureHandle_[2]); // 空の星
		}
	}

	// 行列を更新
	worldTransfrom_.UpdateMatrix();
}

void UI::Draw() { 
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);
	// 数字描画
	sprite_->Draw();
	// 星描画
	for (int i = 0; i < 5; i++) {
		spriteStar_[i]->Draw();
	}
	// プライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
}
