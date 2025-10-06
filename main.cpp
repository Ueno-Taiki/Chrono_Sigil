#include <Windows.h>
#include "KamataEngine.h"
#include "Code/TitleScene.h"
#include "Code/GameScene.h"
#include "Code/UI.h"

using namespace KamataEngine;

TitleScene* titleScene = nullptr;
GameScene* gameScene = nullptr;
UI* ui = nullptr;

// シーン
enum class Scene {

	kUnknown = 0,

	kTitle,
	kGame
};

// 現在シーン
Scene scene = Scene::kUnknown;

// シーン切り替え処理
void ChangeScene();

// シーンの更新
void UpdateScene();

// シーンの描画
void DrawScene();

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	// エンジンの初期化
	KamataEngine::Initialize(L"LE3D_01_ウエノ_タイキ_Chrono_Sigil");

	// DirectXCommonインスタンスの取得
	DirectXCommon *dxCommon = DirectXCommon::GetInstance();

	// 最初のシーンの初期化
	scene = Scene::kTitle;
	titleScene = new TitleScene;
	titleScene->Initialize();

	// メインループ
	while (true) {
		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

		// シーン切り替え
		ChangeScene();
		// 現在のシーン
		UpdateScene();

		// 描画開始
		dxCommon->PreDraw();

		// 現在のシーンの描画
		DrawScene();

		//描画終了
		dxCommon->PostDraw();
	}

	// 各種解放
	delete titleScene;
	delete gameScene;
	delete ui;

	// エンジンの終了処理
	KamataEngine::Finalize();

	return 0;
}

// シーン切り替え処理
void ChangeScene() {
	switch (scene) {
		case Scene::kTitle:
		if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
			// シーンの変更
			scene = Scene::kGame;
			// 旧シーンの解放
			delete titleScene;
			titleScene = nullptr;
			// 新シーンの生成と初期化
			gameScene = new GameScene;
			gameScene->Initialize();
			ui = new UI();
			ui->Initialize();
		}
		break;
		case Scene::kGame:
		// タイトルに戻る
		if (ui->IsProgress()) {
			// シーンの変更
			scene = Scene::kTitle;
			// 旧シーンの解放
			delete gameScene;
			gameScene = nullptr;
			delete ui;
			ui = nullptr;
			// 新シーンの生成と初期化
			titleScene = new TitleScene();
			titleScene->Initialize();
		}
		break;
	}
}

// シーンの更新
void UpdateScene() {
	switch (scene) {
		case Scene::kTitle:
		titleScene->Update();
		break;
		case Scene::kGame:
		// UIが開いていなければゲームを進める
		if (!ui->IsActive()) {
			gameScene->Update();
		}
		ui->Update();
		break;
	}
}

// シーンの描画
void DrawScene() {
	switch (scene) {
		case Scene::kTitle:
		titleScene->Draw();
		break;
		case Scene::kGame:
		gameScene->Draw();
		ui->Draw();
		break;
	}
}