#pragma once
#include <array>
#include <vector>
#include "KamataEngine.h"

// カードを処理するクラス
class Card {
public:
	~Card();

	void Initialize();

	void Update();

	void Draw();

	// カード移動
	void CardMove();

	// カード選択
	void CardSelect();

	// カードの処理判定
	void CardProcessing();

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransfrom_;

	// カードの枚数
	static inline const int CARD_NUM = 5;

	// カードデータ
	struct CardData {
		KamataEngine::Vector2 position;
		KamataEngine::Vector2 targetPos;

		float moveSpeed;

		bool isOpen;

		// カート選択
		bool isSelect = false;

		// 中央移動フラグ
		bool isCenter = false;

		// 消えるフラグ
		bool isDead = false;

		int frontTextureIndex;

		KamataEngine::Sprite* sprite;
	};

	// カード
	CardData cards_[CARD_NUM];

	// テクスチャハンドル
	uint32_t textureHandle_[4];

	// 最終到着位置
	bool isAllMove_ = false;
};

