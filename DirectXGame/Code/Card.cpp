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
		cards_[i].targetPos = { 100.0f + i * 230.0f, 300.0f };

		// 移動速度
		cards_[i].moveSpeed = 8.0f;

		//	到着フラグ
		cards_[i].isOpen = false;
	}
}

void Card::Update() { 
	// カード移動
	CardMove();

	// カード選択
	CardSelect();

	// 行列の更新
	worldTransfrom_.UpdateMatrix();
}

void Card::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);
	// カードの描画
	for (int i = 0; i < CARD_NUM; i++) {
		if (cards_[i].isDead) {
			continue;
		}
		cards_[i].sprite->Draw();
	}
	// プライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
}

// カード移動
void Card::CardMove() {
	// 全カード到着チェック
	bool allOpen = true;

	for (int i = 0; i < CARD_NUM; i++) {
		// 最初の到着
		if (!isAllMove_) {
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
			// 全カード到着確認
			if (!cards_[i].isOpen) {
				allOpen = false;
			}
		}
	}

	// 全部到着したら次のフェーズ
	if (allOpen) {
		isAllMove_ = true;
	}

	// 左下へ移動
	if (isAllMove_) {
		int aliveIndex = 0; // 生存カード用の並び番号

		for (int i = 0; i < CARD_NUM; i++) {

			// 消えたカードは処理しない
			if (cards_[i].isDead) {
				continue;
			}

			// 中央へ移動するカード
			if (cards_[i].isCenter) {

				Vector2 centerPos = { 565.0f, 135.0f };

				cards_[i].position.x += (centerPos.x - cards_[i].position.x) * 0.1f;
				cards_[i].position.y += (centerPos.y - cards_[i].position.y) * 0.1f;

				// 中央到着で消える
				float dx = centerPos.x - cards_[i].position.x;
				float dy = centerPos.y - cards_[i].position.y;

				if (abs(dx) < 1.0f && abs(dy) < 1.0f) {
					cards_[i].isDead = true;
					cards_[i].isCenter = false;
				}
			}
			// 通常カード
			else {
				// aliveIndex を使う
				Vector2 handPos = { 0.0f + aliveIndex * 150.0f, 470.0f };

				// 選択中なら少し上
				if (cards_[i].isSelect) {
					handPos.y -= 30.0f;
				}
				cards_[i].position.x += (handPos.x - cards_[i].position.x) * 0.1f;
				cards_[i].position.y += (handPos.y - cards_[i].position.y) * 0.1f;
				aliveIndex++; // 生存カードだけ増やす
			}
		}
	}

	// スプライト反映
	for (int i = 0; i < CARD_NUM; i++) {
		cards_[i].sprite->SetPosition(cards_[i].position);
	}
}

// カード選択
void Card::CardSelect() {
	// マウス座標取得
	Vector2 mousePos = {
		float(input_->GetMousePosition().x),
		float(input_->GetMousePosition().y)
	};

	//左クリック
	if (input_->IsTriggerMouse(0)) {
		for (int i = 0; i < CARD_NUM; i++) {
			// カードサイズ
			float width = 150.0f;
			float height = 250.0f;

			// 当たり判定
			bool isHit = mousePos.x >= cards_[i].position.x && mousePos.x <= cards_[i].position.x + width &&
				mousePos.y >= cards_[i].position.y && mousePos.y <= cards_[i].position.y + height;

			if (isHit) {
				cards_[i].isSelect = true;
			}
			else {
				cards_[i].isSelect = false;
			}
		}
	}

	// ENTERキー
	if (input_->TriggerKey(DIK_RETURN)) {
		for (int i = 0; i < CARD_NUM; i++) {
			if (cards_[i].isSelect) {
				cards_[i].isCenter = true;
			}
		}
	}
}
