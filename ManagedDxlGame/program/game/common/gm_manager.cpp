#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_manager.h"
#include "../common/gm_scene_base.h"

// コンストラクタ
GameManager::GameManager(SceneBase* start_scene) : now_scene_(start_scene) {
	tansition_graph_hdl_ = LoadGraph("graphics/black.bmp");
	SetFontSize(50);
}

// ゲームマネージャーのアドレスを返す
GameManager* GameManager::GetInstance(SceneBase* start_scene) {
	static GameManager* instance = nullptr;
	if (!instance) {
		instance = new GameManager(start_scene);
	}
	return instance;
}

// アドレスを削除
void GameManager::Destroy() {
	delete GetInstance();
}

// next_scene_をセット
void GameManager::changeScene(SceneBase* next_scene, float trans_time) {
	// 遷移中の場合は処理を中断
	if (isTransitioning_) return;

	next_scene_ = next_scene;
	trans_time_ = trans_time;

	sequence_.change(&GameManager::seqTransOut);
	isTransitioning_ = true;  // 遷移中フラグを立てる
}

// now_scene_のアップデート
void GameManager::update(float delta_time) {

	if (now_scene_) now_scene_->update(delta_time);
	if (now_scene_) now_scene_->draw();

	sequence_.update(delta_time);

}

// 徐々に暗くする
bool GameManager::seqTransOut(const float delta_time) {
	//DrawStringEx(10, 10, 0xffff00, "seqTransOut");
    int alpha = (sequence_.getProgressTime() / trans_time_ * 255.0f);
    if (alpha >= 255) {
		// ↓ここでシーンの切り替え
        sequence_.change(&GameManager::seqTransIn);
        delete now_scene_;
        now_scene_ = nullptr;
        now_scene_ = next_scene_;
    }
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, tansition_graph_hdl_, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
    return true;
}

// 徐々に明るくする
bool GameManager::seqTransIn(const float delta_time) {
	int alpha = 255 - (sequence_.getProgressTime() / trans_time_ * 255.0f);
	//DrawStringEx(10, 10, 0xffff00, "seqTransIn");
	if (alpha <= 0) {
		sequence_.change(&GameManager::seqRunScene);
		isTransitioning_ = false;  // 遷移中フラグを解除
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, tansition_graph_hdl_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	return true;
}

// 何もしない
bool GameManager::seqRunScene(const float delta_time) {
	//DrawStringEx(10, 10, 0xffff00, "seqRunScene");
	return true;
}