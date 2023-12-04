#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_scene_play.h"
#include "gm_scene_result.h"
#include "../common/gm_manager.h"

//魔法の言葉 ( コンストラクタ )
ScenePlay::ScenePlay() {

	player_ = new Player();
	score_ = new Score();

}


// デストラクタ
ScenePlay::~ScenePlay() {
	
	auto it = enemy_.begin();
	while (it != enemy_.end()) {
		delete *it;
		it = enemy_.erase(it);
		continue;
	}
	delete player_;
	player_ = nullptr;
	delete score_;
	score_ = nullptr;
}


void ScenePlay::update(float delta_time) {

	sequence_.update(delta_time);

}

void ScenePlay::draw() {
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, background_1_y , 1.0f, 0, back_ground_gfx_[0], false);
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, background_2_y, 1.0f, 0, back_ground_gfx_[1], false);
	//enemy_->draw();

	auto it = enemy_.begin();
	while (it != enemy_.end()) {
		(*it)->draw();
		it++;

	}

	player_->draw();
	//フレームの表示
	
	if (first_judge) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, black_power_);
		DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, black_gfx_, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	if (finish_judge) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, black_power2_);
		DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, black_gfx_, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 1.0f, 0, frame_gfx_, true);

	//ハ－トの表示
	for(int i = 0;i < fish_hp_;i++)
		DrawRotaGraph(heart_pos.x + i * 75, heart_pos.y, 0.75f, 0, heart_gfx_, true);

	SetFontSize(70);
	DrawStringEx(eat_pos.x + 100, eat_pos.y + 50, 0, "%d", eat_count_need - eat_count);
	DrawStringEx(level_pos.x + 180, level_pos.y - 10, 0, "%d", level_);
	SetFontSize(30);
	score_->draw();
	DrawStringEx(level_pos.x, level_pos.y, 0x000080, "レベル");
	SetFontSize(25);
	DrawStringEx(eat_pos.x, eat_pos.y, 0x000080, "レベルアップまで\n\nあと");
	SetFontSize(30);
	DrawStringEx(feed_pos.x, feed_pos.y, 0x000080, "捕食出来る\nおさかな");
	SetFontSize(50);

	DrawRotaGraph(fish1_icon_pos.x, fish1_icon_pos.y, 1.0f, 0, icon_gfx_[0][0], false);
	DrawRotaGraph(fish2_icon_pos.x, fish2_icon_pos.y, 1.0f, 0, icon_gfx_[fish2_icon_release][1], false);
	DrawRotaGraph(fish3_icon_pos.x, fish3_icon_pos.y, 1.0f, 0, icon_gfx_[fish3_icon_release][2], false);
	DrawRotaGraph(fish4_icon_pos.x, fish4_icon_pos.y, 1.0f, 0, icon_gfx_[fish4_icon_release][3], false);
	DrawRotaGraph(fish5_icon_pos.x, fish5_icon_pos.y, 1.0f, 0, icon_gfx_[fish5_icon_release][4], false);


	//debug
	/*DrawStringEx(500, 400, -1, "%f", player_->get_fish_pos_().y);
	DrawStringEx(400, 100, -1, "hp = %d", fish_hp_);
	DrawStringEx(400, 150, -1, "level = %d", level_);
	DrawStringEx(400, 200, -1, "count = %d", eat_count);
	DrawStringEx(400, 350, -1, "score = %d", finalscore_);*/
	//DrawStringEx(400, 100, -1, "elapsed = %f", elapsed_);

	//カウントダウン
	if (first_judge) {
		if (count_number >= 1) {
			DrawRotaGraph(game_window_width / 2, game_window_height / 2,
				0.5f * (1 - elapsed_ * 0.8f), 0, count_gfx_[count_number], true);
		}
		if(count_number == 0)
			DrawRotaGraph(game_window_width / 2, game_window_height / 2,
				1.0f, 0, count_gfx_[count_number], true);
	}
}

//敵を出したり当たったり
void ScenePlay::EnemyProcess(float delta_time) {

	if (interval_delta_time <= 0 && !finish_judge) {
		enemy_.emplace_back(new Enemy());
		interval_delta_time = interval_time;
	}//敵を一定間隔で生成
	interval_delta_time -= 1;
	//int y = 200;
	auto it = enemy_.begin();

	while (it != enemy_.end()) {

		(*it)->update(delta_time);

		if (!finish_judge) {
			//ぶつかった時の処理
			tnl::Vector3 dummy_pos = player_->get_fish_pos_();
			int n = tnl::IsIntersectRectToCorrectPosition(
				dummy_pos, player_->get_fish_pos_(), player_->get_fish_size_().x, player_->get_fish_size_().y,
				(*it)->fish_pos_, (*it)->fish_size_.x, (*it)->fish_size_.y);


			if (n != 0) {

				if ((*it)->feed_judge) {//餌と当たった時

					if ((*it)->enemy_sort_ == (*it)->fish1)score_->set_score1_judge(true);
					if ((*it)->enemy_sort_ == (*it)->fish2)score_->set_score2_judge(true);
					if ((*it)->enemy_sort_ == (*it)->fish3)score_->set_score3_judge(true);
					if ((*it)->enemy_sort_ == (*it)->fish4)score_->set_score4_judge(true);
					if ((*it)->enemy_sort_ == (*it)->fish5)score_->set_score5_judge(true);
					//score_->set_score_judge(true);
					eat_count++; 
					PlaySoundMem(se_sound[2], DX_PLAYTYPE_BACK);

					delete* it;
					it = enemy_.erase(it);
					continue;
				}
				else if(!player_->get_damaged_judge_()){//敵と当たった時
					player_->set_hp_(fish_hp_ -= 1);
					player_->set_damaged_judge_(true);
					PlaySoundMem(se_sound[3], DX_PLAYTYPE_BACK);
					if(fish_hp_ <= 0)PlaySoundMem(se_sound[5], DX_PLAYTYPE_BACK);
				}
			}
		}

		//画面外で消去
		if ((*it)->fish_pos_.x >= DXE_WINDOW_WIDTH || (*it)->fish_pos_.x <= 0) {
			delete* it;
			it = enemy_.erase(it);
			continue;
		}
		it++;
		//y += 50;
	}

	if (eat_count >= eat_count_need) {
		level_++;
		eat_count_need++;
		eat_count = 0;
		if(level_ <= 5)interval_time -= interval_time_decrease;
		else interval_time -= interval_time_decrease * 0.2f;
		//レベルアップごとに敵が沸きやすくなる
		PlaySoundMem(se_sound[4], DX_PLAYTYPE_BACK);
		if (level_ == 2)fish2_icon_release = false;
		if (level_ == 3)fish3_icon_release = false;
		if (level_ == 4)fish4_icon_release = false;
		if (level_ == 5)fish5_icon_release = false;
	}
}

void ScenePlay::SoundChange(){
	if (level_ >= 4 && !sound_change_jadge) {
		PlaySoundMem(game_sound[1], DX_PLAYTYPE_LOOP);
		sound_change_jadge = true;
	}
};

void ScenePlay::Highlevel(float delta_time) {
	if (level_ >= 4 && !highlevel_jadge_change_jadge) {
		if (!highlevel_jadge_se_jadge) {
			PlaySoundMem(se_sound[6], DX_PLAYTYPE_BACK);
			highlevel_jadge_se_jadge = true;
			player_->set_highlevel_jadge_(true);
		}
		process_now = true;
		StopSoundMem(game_sound[0]);

		elapsed_ += delta_time;
		background_1_y -= elapsed_ * 2.5f;
		background_2_y -= elapsed_ * 2.5f;

		if (background_2_y <= DXE_WINDOW_HEIGHT / 2) {
			background_2_y = DXE_WINDOW_HEIGHT / 2;
			highlevel_jadge_change_jadge = true;
			process_now = false;
			elapsed_ = 0;
			StopSoundMem(se_sound[6]);
		}
	}
}

void ScenePlay::CountDown(float delta_time) {
	elapsed_ += delta_time;
	if (count_number == 4) {
		count_number = 3;
		PlaySoundMem(se_sound[0], DX_PLAYTYPE_BACK);
	}
	if (count_number == 3 && elapsed_ >= count_speed) {
		count_number = 2;
		elapsed_ = 0;
		PlaySoundMem(se_sound[0], DX_PLAYTYPE_BACK);
	}
	if (count_number == 2 && elapsed_ >= count_speed) {
		count_number = 1;
		elapsed_ = 0;
		PlaySoundMem(se_sound[0], DX_PLAYTYPE_BACK);
	}
	if (count_number == 1 && elapsed_ >= count_speed) {
		count_number = 0;
		elapsed_ = 0;
		PlaySoundMem(se_sound[1], DX_PLAYTYPE_BACK);
	}
	if (count_number == 0 && elapsed_ >= count_speed) {
		count_number = -1;
		elapsed_ = 0;
		process_now = false;
		first_judge = false;
		PlaySoundMem(game_sound[0], DX_PLAYTYPE_LOOP);
		//ここでゲームスタートの合図
	}
};

void ScenePlay::GameOver() {
	finish_judge = true;
	fade_value--; 
	StopSoundMem(game_sound[0]);
	StopSoundMem(game_sound[1]);
	if (fade_value <= 0) {
		finalscore_ = score_->get_scorepoint();
		//result画面へ遷移
		auto mgr = GameManager::GetInstance();
		mgr->changeScene(new SceneResult(finalscore_));
		//mgr->changeScene(new SceneResult(finalscore_, highscore_));
	}
}

bool ScenePlay::seqStart(const float delta_time) {
	if (sequence_.isStart()) {
		black_gfx_ = LoadGraph("graphics/black.bmp");
		back_ground_gfx_[0] = LoadGraph("graphics/umi.png");
		back_ground_gfx_[1] = LoadGraph("graphics/umi2.png");
		frame_gfx_ = LoadGraph("graphics/frame.png");
		heart_gfx_ = LoadGraph("graphics/heart.png");
		count_gfx_[0] = LoadGraph("graphics/Start.png");
		count_gfx_[1] = LoadGraph("graphics/1.png");
		count_gfx_[2] = LoadGraph("graphics/2.png");
		count_gfx_[3] = LoadGraph("graphics/3.png");
		icon_gfx_[0][0] = LoadGraph("graphics/icon_fish1.png");
		icon_gfx_[0][1] = LoadGraph("graphics/icon_fish2.png");
		icon_gfx_[0][2] = LoadGraph("graphics/icon_fish3.png");
		icon_gfx_[0][3] = LoadGraph("graphics/icon_fish4.png");
		icon_gfx_[0][4] = LoadGraph("graphics/icon_fish5.png");
		icon_gfx_[1][1] = LoadGraph("graphics/icon_fish2_s.png");
		icon_gfx_[1][2] = LoadGraph("graphics/icon_fish3_s.png");
		icon_gfx_[1][3] = LoadGraph("graphics/icon_fish4_s.png");
		icon_gfx_[1][4] = LoadGraph("graphics/icon_fish5_s.png");
		game_sound[0] = LoadSoundMem("sound/umi.mp3");
		game_sound[1] = LoadSoundMem("sound/umi2.mp3");
		se_sound[0] = LoadSoundMem("sound/se/count.mp3");
		se_sound[1] = LoadSoundMem("sound/se/start.mp3");
		se_sound[2] = LoadSoundMem("sound/se/eat.mp3");
		se_sound[3] = LoadSoundMem("sound/se/damage.mp3");
		se_sound[4] = LoadSoundMem("sound/se/powerup.mp3");
		se_sound[5] = LoadSoundMem("sound/se/death.mp3");
		se_sound[6] = LoadSoundMem("sound/se/gogogo.mp3");

		process_now = true;
		first_judge = true;

	}

	if (!GameManager::GetInstance()->getTransitionFlg()) {
		sequence_.change(&ScenePlay::seqIdle);
	}
	return true;
}

bool ScenePlay::seqIdle(float delta_time) {
	if (sequence_.isStart()) {
	}

	if(first_judge)CountDown(delta_time);
	if (level_ >= 4)Highlevel(delta_time);

	if (!finish_judge && !process_now ) {
		player_->update(delta_time);
		score_->update(delta_time);
		EnemyProcess(delta_time);
		SoundChange();
	}
	if (fish_hp_ <= 0)GameOver();

	//result画面へ遷移

	/*if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		auto mgr = GameManager::GetInstance();
		mgr->changeScene( new SceneTitle() );
	}*/

	//デバッグ
	/*if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		fish_hp_ = 0;
	}*/
	//デバッグ
	/*if (tnl::Input::IsKeyDownTrigger(eKeys::KB_1))fish_hp_ = 1;
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_2))fish_hp_ = 2;
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_3))fish_hp_ = 3;
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_4))level_ = 4;*/


	return true;

}
