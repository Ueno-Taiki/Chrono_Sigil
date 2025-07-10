#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include "Enemy.h"
#include "Skydome.h"

class GameScene {
public:
	~GameScene();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransfrom_;

	// カメラ
	KamataEngine::Camera camera_;

	// プレイヤー
	Player* player_ = nullptr;
	// プレイヤーモデル
	KamataEngine::Model* modelPlayer_ = nullptr;

	// 敵
	Enemy* enemy_ = nullptr;
	// 敵モデル
	KamataEngine::Model* modelEnemy_ = nullptr;

	// 天球
	Skydome* skydome_ = nullptr;
	// 天球モデル
	KamataEngine::Model* modelSkydome_ = nullptr;

	// サウンドデータハンドル
	uint32_t BGM = 0;

	// 音声再生ハンドル
	uint32_t voiceHandle_ = 0;
};

