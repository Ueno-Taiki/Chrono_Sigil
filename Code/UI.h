#pragma once
#include "KamataEngine.h"

class UI{
public:
	~UI();

	void Initialize();

	void Update();

	void Draw();

	// 数字用処理
	void Number();

	// 星の表示を更新
	void Star();

	// 攻撃選択の種類
	void Type();

	// 一時停止の判定
	void Pause();

	// カーソル移動
	void MoveC();

	// UI起動のgetter
	bool IsActive() const { return Uiflag; }

	// ゲーム進行のgetter
	bool IsProgress() const { return Progress; }

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	// 攻撃判別
	enum Attack {
		NormalAttack,
		Skill
	};
	Attack attack = NormalAttack;

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransfrom_;

	// テクスチャハンドル
	uint32_t textureHandle_[8];

	// 数字用スプライト
	KamataEngine::Sprite* sprite_ = nullptr;

	// 星用スプライト
	KamataEngine::Sprite* spriteStar_[5];

	// 一時停止ボタン用スプライト
	KamataEngine::Sprite* spritePause_[3];

	// 攻撃・スキル
	KamataEngine::Sprite* SpriteAttack_[2];

	// SP
	int sp = 3;

	// 文字のサイズ
	KamataEngine::Vector2 size = { 32.0f, 64.0f };

	// サウンドデータハンドル
	uint32_t Click = 0;

	// 音声再生ハンドル
	uint32_t voiceHandle_ = 0u;

	// カーソル
	int moveC = 0;

	// UI起動フラグ
	bool Uiflag = false;

	// ゲーム進行フラグ
	bool Progress = false;
};