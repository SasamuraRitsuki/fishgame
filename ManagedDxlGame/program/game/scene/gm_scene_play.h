#pragma once
#include "../common/gm_scene_base.h"
#include "../gm_obj/gm_player.h"
#include "../gm_obj/gm_enemy.h"
#include "../gm_obj/gm_score.h"

class ScenePlay : public SceneBase {
public :
	ScenePlay();
	~ScenePlay();

	void update(float delta_time) override ;
	void draw() override;
	void EnemyProcess(float delta_time);
	void CountDown(float delta_time);
	void Highlevel(float delta_time);
	void SoundChange();
	void GameOver();

	int level_ = 1;

	int GetFinalScore() const { return finalscore_; }


	int getLevel() const { return level_; }

	int finalscore_ = 0;
private :

	Player* player_ = nullptr;
	Score* score_ = nullptr;
	std::list<Enemy*> enemy_;
	
	tnl::Sequence<ScenePlay> sequence_ = tnl::Sequence<ScenePlay>(this, &ScenePlay::seqStart);
	bool seqStart(const float delta_time);
	bool seqIdle(const float delta_time) ;

	bool process_now = false;
	float game_window_width = DXE_WINDOW_WIDTH - 260;//�t���[���l���̉�
	float game_window_height = DXE_WINDOW_HEIGHT - 80;//�t���[���l���̏c

	int game_sound[2] = {0};
	int se_sound[7] = { 0 };

	float interval_time = 50.0f;//�G���o�Ă���p�x
	int interval_time_decrease = 4;//���x���A�b�v�ŒZ���Ȃ�G�������Ԃ̗�
	float interval_delta_time;
	int back_ground_gfx_[2];
	int icon_gfx_[2][5];
	int frame_gfx_ = 0;
	int count_gfx_[4] = {0};
	int black_gfx_;
	int heart_gfx_;
	int black_power_ = 150;//���̔Z���n��
	int black_power2_ = 100;//���̔Z���I���

	//int score_ = 0;
	bool first_judge = false;//�͂��܂�t���O
	bool finish_judge = false;//����t���O
	bool sound_change_jadge = false;//���y�ύX�t���O
	bool highlevel_jadge_change_jadge = false;//�w�i�ύX�t���O
	bool highlevel_jadge_se_jadge = false;//�w�i�ύX����se�t���O
	int fish_hp_ = 3;
	int eat_count = 0;
	int eat_count_need = 4;//���x���A�b�v�ɕK�v�ȉa�̐�
	int test = 0;
	float fade_value = 100;//�Ó]�܂ł̎���
	float elapsed_ = 0;
	int count_number = 4;
	float count_speed = 0.75f;//�J�E���g�_�E���̑���

	tnl::Vector3 eat_pos = { 1040,200,0 };
	tnl::Vector3 level_pos = { 1040,110,0 };
	tnl::Vector3 feed_pos = { 1040,330,0 };
	tnl::Vector3 heart_pos = { 820,40,0 };
	tnl::Vector3 fish1_icon_pos = { 1080,450,0 };
	tnl::Vector3 fish2_icon_pos = { fish1_icon_pos.x + 80,fish1_icon_pos.y,0 };
	tnl::Vector3 fish3_icon_pos = { fish2_icon_pos.x + 80,fish1_icon_pos.y,0 };
	tnl::Vector3 fish4_icon_pos = { fish1_icon_pos.x + 35,fish1_icon_pos.y + 90,0 };
	tnl::Vector3 fish5_icon_pos = { fish4_icon_pos.x + 80,fish4_icon_pos.y,0 };
	bool fish2_icon_release = true;
	bool fish3_icon_release = true;
	bool fish4_icon_release = true;
	bool fish5_icon_release = true;
	int background_1_y = DXE_WINDOW_HEIGHT / 2;
	int background_2_y = DXE_WINDOW_HEIGHT / 2 + game_window_height + 10;
	
};

