#include "Card.h"
#include <cassert>

using namespace KamataEngine;

Card::~Card() { 
	for (int i = 0; i < CARD_NUM; i++) {
		delete cards_[i].sprite;
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
	textureHandle_[0] = TextureManager::Load("Card/BackCard.png");
	textureHandle_[1] = TextureManager::Load("Card/Strength.png");
	textureHandle_[2] = TextureManager::Load("Card/Lower_defense.png");
	textureHandle_[3] = TextureManager::Load("Card/Sp.png");
	
	// ランダム変数
	srand((unsigned int) time(nullptr));

	for (int i = 0; i < CARD_NUM; i++) {

		// ランダム表カード
		cards_[i].frontTextureIndex = 1 + rand() % 3;

		// 最初は裏カード
		cards_[i].sprite = Sprite::Create(textureHandle_[0], { -300.0f, 300.0f });

		// 左側からスタート
		cards_[i].position = { -300.0f, 300.0f };

		// 定位置
		cards_[i].targetPos = { 150.0f + i * 220.0f, 300.0f };

		// 移動速度
		cards_[i].moveSpeed = 8.0f;

		//	到着フラグ
		cards_[i].isOpen = false;
	}
}

void Card::Update() { 
	// カード移動
	CardMove();
}

void Card::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);
	// カードの描画
	for (int i = 0; i < CARD_NUM; i++) {
		cards_[i].sprite->Draw();
	}
	// プライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
}

// カード移動
void Card::CardMove() {
	for (int i = 0; i < CARD_NUM; i++) {
		// 左から移動
		if (!cards_[i].isOpen) {
			cards_[i].position.x += cards_[i].moveSpeed;
			// 到着したら表カードへ変更
			if (cards_[i].position.x >= cards_[i].targetPos.x) {
				cards_[i].position.x = cards_[i].targetPos.x;
				cards_[i].sprite->SetTextureHandle(textureHandle_[cards_[i].frontTextureIndex]);
				cards_[i].isOpen = true;
			}
		}
		// 位置反映
		cards_[i].sprite->SetPosition(cards_[i].position);
	}
}

