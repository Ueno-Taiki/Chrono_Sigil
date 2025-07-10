#pragma once

#include <memory>
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
	std::unique_ptr<Player> player_;
	// プレイヤーモデル
	std::unique_ptr<KamataEngine::Model> modelPlayer_;

	// 敵
	std::unique_ptr<Enemy> enemy_;
	// 敵モデル
	std::unique_ptr<KamataEngine::Model> modelEnemy_;

	// 天球
	std::unique_ptr<Skydome> skydome_;
	// 天球モデル
	std::unique_ptr<KamataEngine::Model> modelSkydome_;

	// サウンドデータハンドル
	uint32_t BGM = 0;

	// 音声再生ハンドル
	uint32_t voiceHandle_ = 0;
};

