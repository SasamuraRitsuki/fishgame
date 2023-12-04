#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_manager.h"
#include "../common/gm_scene_base.h"

// �R���X�g���N�^
GameManager::GameManager(SceneBase* start_scene) : now_scene_(start_scene) {
	tansition_graph_hdl_ = LoadGraph("graphics/black.bmp");
	SetFontSize(50);
}

// �Q�[���}�l�[�W���[�̃A�h���X��Ԃ�
GameManager* GameManager::GetInstance(SceneBase* start_scene) {
	static GameManager* instance = nullptr;
	if (!instance) {
		instance = new GameManager(start_scene);
	}
	return instance;
}

// �A�h���X���폜
void GameManager::Destroy() {
	delete GetInstance();
}

// next_scene_���Z�b�g
void GameManager::changeScene(SceneBase* next_scene, float trans_time) {
	// �J�ڒ��̏ꍇ�͏����𒆒f
	if (isTransitioning_) return;

	next_scene_ = next_scene;
	trans_time_ = trans_time;

	sequence_.change(&GameManager::seqTransOut);
	isTransitioning_ = true;  // �J�ڒ��t���O�𗧂Ă�
}

// now_scene_�̃A�b�v�f�[�g
void GameManager::update(float delta_time) {

	if (now_scene_) now_scene_->update(delta_time);
	if (now_scene_) now_scene_->draw();

	sequence_.update(delta_time);

}

// ���X�ɈÂ�����
bool GameManager::seqTransOut(const float delta_time) {
	//DrawStringEx(10, 10, 0xffff00, "seqTransOut");
    int alpha = (sequence_.getProgressTime() / trans_time_ * 255.0f);
    if (alpha >= 255) {
		// �������ŃV�[���̐؂�ւ�
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

// ���X�ɖ��邭����
bool GameManager::seqTransIn(const float delta_time) {
	int alpha = 255 - (sequence_.getProgressTime() / trans_time_ * 255.0f);
	//DrawStringEx(10, 10, 0xffff00, "seqTransIn");
	if (alpha <= 0) {
		sequence_.change(&GameManager::seqRunScene);
		isTransitioning_ = false;  // �J�ڒ��t���O������
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, tansition_graph_hdl_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	return true;
}

// �������Ȃ�
bool GameManager::seqRunScene(const float delta_time) {
	//DrawStringEx(10, 10, 0xffff00, "seqRunScene");
	return true;
}