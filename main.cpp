#include <Novice.h>
#include "./Function/Include/struct.h"
#include "./Camera/Include/Camera.h"
#include "./Camera/Include/BackFrame.h"
#include "BoxClass.h"
const char kWindowTitle[] = "LC1A_20_ヒサイチ_コウキ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	
	Novice::Initialize(kWindowTitle, kWindowSizeX, kWindowSizeY);

	Camera* camera = new Camera;
	BackFrame* frame = new BackFrame;

	BoxClass* box = new BoxClass;

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///------------------///
		/// ↓更新処理ここから
		///------------------///

	

		camera->Update(keys);
		frame->Update();
		if (keys[DIK_SPACE]&&!preKeys[DIK_SPACE])
		{
			box->SetVelocity({ 70.0f ,0 });
		}
		box->Update();


		///------------------///
		/// ↑更新処理ここまで
		///------------------///

		///------------------///
		/// ↓描画処理ここから
		///------------------///


		frame->Draw(camera);

		box->Draw(camera);
		box->Debug();


		///------------------///
		/// ↑描画処理ここまで
		///------------------///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
