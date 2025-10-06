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
	// 一時停止ボタン削除
	for (int i = 0; i < 3; i++) {
		delete spritePause_[i];
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
	textureHandle_[3] = TextureManager::Load("UI/Pause.png");
	textureHandle_[4] = TextureManager::Load("UI/Pose1.png");
	textureHandle_[5] = TextureManager::Load("UI/Pose2.png");

	// BGM・SE読み込み
	Click = audio_->LoadWave("SE/Click.wav");

	// 数字用スプライト
	sprite_ = Sprite::Create(textureHandle_[0], { 750, 640 });
	sprite_->SetSize(size);

	// 星を5つ作成して横並びに配置
	for (int i = 0; i < 5; i++) {
		spriteStar_[i] = Sprite::Create(textureHandle_[1], { 800.0f + i * 36.0f, 652.0f });
		spriteStar_[i]->SetSize({ 32.0f, 32.0f });
	}

	// 一時停止ボタン用スプライト	
	spritePause_[0] = Sprite::Create(textureHandle_[3], { 1216, 0 });
	spritePause_[1] = Sprite::Create(textureHandle_[4], { 320, 180});
	spritePause_[2] = Sprite::Create(textureHandle_[5], { 320, 180 });
}

void UI::Update() { 
	// 数字用処理
	Number();

	// 星の表示を更新
	Star();

	// 一時停止の判定
	Pause();

	// カーソル移動
	MoveC();

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
	// 一時停止ボタン用描画
	spritePause_[0]->Draw();
	// ポーズ描画
	if (Uiflag && moveC == 0) {
		spritePause_[1]->Draw();
	}
	if (Uiflag && moveC == 1) {
		spritePause_[2]->Draw();
	}
	// プライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
}

// 数字用処理
void UI::Number() {
	int nowNumber = sp % 10;
	sprite_->SetTextureRect({ size.x * nowNumber, 0 }, size);
}

// 星の表示を更新
void UI::Star() {
	int starCount = min(sp, 5);
	for (int i = 0; i < 5; i++) {
		if (i < starCount) {
			spriteStar_[i]->SetTextureHandle(textureHandle_[1]); // 塗りつぶし
		}
		else {
			spriteStar_[i]->SetTextureHandle(textureHandle_[2]); // 空の星
		}
	}
}

// 一時停止の判定
void UI::Pause() {
	// 設定を開く
	if (Input::GetInstance()->IsTriggerMouse(0)) {
		// マウスの位置取得
		Vector2 v = Input::GetInstance()->GetMousePosition();

		if (v.x >= 1216 && v.y <= 64) {
			audio_->PlayWave(Click, false);
			Uiflag = true;
		}
	}
}

// カーソル移動
void UI::MoveC() {
	// 移動
	if (input_->TriggerKey(DIK_W)) {
		moveC = 0;
	}
	if (input_->TriggerKey(DIK_S)) {
		moveC = 1;
	}

	// 決定
	if (input_->PushKey(DIK_RETURN) && moveC == 0) {
		Uiflag = false;
	}
	if (input_->PushKey(DIK_RETURN) && moveC == 1) {
		Progress = true;
	}
}
