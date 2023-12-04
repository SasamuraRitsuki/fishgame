#include "../../dxlib_ext/dxlib_ext.h"
//#include "../common/gm_manager.h"
//#include "../scene/gm_scene_play.h"
#include "gm_score.h"

//�R���X�g���N�^�i�ŏ��Ɉ�x�������s�j
Score::Score() {
	
}

// �f�X�g���N�^
Score::~Score() {

}


void Score::update(float delta_time) {
	if (score1_judge) {
		_scorepoint += 1;
		score1_judge = false;
	}
	if (score2_judge) {
		_scorepoint += 2;
		score2_judge = false;
	}
	if (score3_judge) {
		_scorepoint += 3;
		score3_judge = false;
	}
	if (score4_judge) {
		_scorepoint += 4;
		score4_judge = false;
	}
	if (score5_judge) {
		_scorepoint += 5;
		score5_judge = false;
	}
}

void Score::draw() {
	DrawStringEx(score_pos.x, score_pos.y, 0x000080, "�X�R�A");
	SetFontSize(55);
	DrawStringEx(score_pos.x + 120, score_pos.y - 10, 0, "%d�_", _scorepoint);
	SetFontSize(50);
	
	//�f�o�b�O
	//DrawStringEx(900, 100, -1, "judge = %d", score1_judge);
	//DrawStringEx(900, 150, -1, "sort = %d", enemy_sort_s);

}