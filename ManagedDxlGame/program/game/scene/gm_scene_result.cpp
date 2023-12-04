#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_scene_title.h"
#include "gm_scene_play.h"
#include "gm_scene_result.h"
#include "../common/gm_manager.h"



SceneResult::SceneResult(int score,int highscore) {

	finalscore_ = score;
	highscore_ = highscore;
}

void SceneResult::update(float delta_time) {
	sequence_.update(delta_time);
	elapsed_ += delta_time;
	if (elapsed_ >= 1) {
		if (count_scene == 2) {//ハイスコアつけるなら3
			if (enter_on)enter_on = false;
			else enter_on = true;
		}
		else {
			if (count_scene == 0)PlaySoundMem(se_sound[0], DX_PLAYTYPE_BACK);
			else PlaySoundMem(se_sound[1], DX_PLAYTYPE_BACK);
			count_scene++;
		}
		elapsed_ = 0;
	}

}

void SceneResult::draw() {
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 1.0f, 0, back_ground_gfx_, true);
	if (enter_on)DrawRotaGraph(enter_pos_.x, enter_pos_.y, 1.0f, 0, enter_gfx_, true);

	
	ScenePlay* scene_play =
		static_cast<ScenePlay*>(GameManager::GetInstance()->getSceneInstance());
	int finalscore = scene_play->GetFinalScore();
	
	if (count_scene >= 1) {
		DrawStringEx(400, 200, -1, "ただいまのスコアは...");
	}
	if (count_scene >= 2) {
		SetFontSize(150);
		DrawStringEx(score_pos_.x, score_pos_.y, -1, "%d点", finalscore_);
		SetFontSize(50);
	}
	/*if (count_scene >= 3) {
		SetFontSize(70);
		if(finalscore_ > highscore_)
		DrawStringEx(highscore_pos_.x, highscore_pos_.y, -1, "ハイスコア %d点", finalscore_);
		else
			DrawStringEx(highscore_pos_.x, highscore_pos_.y, -1, "ハイスコア %d点", highscore_);
		SetFontSize(50);
	}*/
}

bool SceneResult::seqIdle(float delta_time) {
	if (sequence_.isStart()) {
		back_ground_gfx_ = LoadGraph("graphics/result.png");
		enter_gfx_ = LoadGraph("graphics/enter.png");
		se_sound[0] = LoadSoundMem("sound/se/score_koka.mp3");
		se_sound[1] = LoadSoundMem("sound/se/score_don.mp3");
		se_sound[2] = LoadSoundMem("sound/se/idou_button.mp3");
	}

	if (count_scene >= 2) {
		if ((tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) ||
			(tnl::Input::IsPadDownTrigger(ePad::KEY_1))) {

			PlaySoundMem(se_sound[2], DX_PLAYTYPE_BACK);

			auto mgr = GameManager::GetInstance();
			mgr->changeScene(new SceneTitle());
			//タイトル画面へ遷移
		}
	}
	return true;
}
