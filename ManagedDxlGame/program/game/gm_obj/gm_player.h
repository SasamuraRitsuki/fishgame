#pragma once


class Player {
public:
	Player();
	~Player();
	void update(float delta_time);
	void draw();

	tnl::Vector3 get_fish_pos_() { return fish_main_pos_; }
	tnl::Vector3 get_fish_size_() { return fish_main_size_; }

	bool get_damaged_judge_() { return damaged_judge_; }
	void set_damaged_judge_(bool b) { damaged_judge_ = b; }
	void set_highlevel_jadge_(bool b) { highlevel_jadge_ = b; }
	void set_hp_(int hp) { fish_hp_p = hp; }

	int fish_hp_p = 3;

private:

	int fish_main_gfx_[2][4];
	int se_sound;
	int muki_ = 2;
	bool highlevel_jadge_ = false;
	float fish_main_size_value_ = 1.0f;

	float game_window_width = DXE_WINDOW_WIDTH - 260;//フレーム考慮の横
	float game_window_height = DXE_WINDOW_HEIGHT - 80;//フレーム考慮の縦

	tnl::Vector3 fish_main_pos_ = { game_window_width / 2, game_window_height / 2,0 };

	tnl::Vector3 fish_main_size_ = {104,48,0};
	const tnl::Vector3 fish_main_size_2_ = { 160,48,0 };
	bool damaged_judge_ = false;
	bool size_resize = false;

	float accelerate_up_ = 0;    // 加速度
	float accelerate_right_ = 0;
	float accelerate_left_ = 0;
	float super_delta_time = 0;

	int elapsed_ = 0;
	int invisible_ = 0;
	bool invisible_on_ = false;
	int damaged_time_ = 150;//ダメージによる取得不能時間
	float up_power = 3.8f;//spaceの上昇量
	float up_power_ren = 5.4f;//連続spaceの上昇量
	float right_power = 4.9f;//横の移動量
	
};