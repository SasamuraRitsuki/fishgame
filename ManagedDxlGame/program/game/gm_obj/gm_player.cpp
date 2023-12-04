#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/gm_manager.h"
#include "../scene/gm_scene_play.h"
#include "gm_player.h"

//コンストラクタ（最初に一度だけ実行）
Player::Player() {
	//fish_main_gfx_ = LoadGraph("graphics/fish_main.png");
	LoadDivGraph(
			"graphics/fish_main.png",//画像のパス
			4,								//総フレーム数
			2,								//横フレーム数
			2,								//縦フレーム数
			128,								//横方向へ 1フレームあたりの幅
			128,								//縦方向へ 1フレームあたりの幅
			fish_main_gfx_[0]);						//画像ハンドルを格納する配列名

	LoadDivGraph("graphics/fish_main2.png", 4, 2, 2, 256, 256, fish_main_gfx_[1]);
		se_sound = LoadSoundMem("sound/se/jump.mp3");
}

// デストラクタ
Player::~Player() {

}


void Player::update(float delta_time) {

	tnl::Vector3 prev_main_fish_pos_ = fish_main_pos_;
	//float prev_accelerate_up = accelerate_up_;
		// ←→キーで左右に移動
	if (fish_main_pos_.x > 0) {
		if (tnl::Input::IsKeyDown(eKeys::KB_LEFT) || tnl::Input::IsKeyDown(eKeys::KB_A)||
			(tnl::Input::IsPadDown(ePad::KEY_LEFT))) {
			accelerate_left_ = -right_power;
			muki_ = 0;
		}
	}
	if (fish_main_pos_.x < game_window_width) {
		if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT) || tnl::Input::IsKeyDown(eKeys::KB_D)||
			(tnl::Input::IsPadDown(ePad::KEY_RIGHT))) {
			accelerate_right_ = right_power;
			muki_ = 2;
		}
	}

	// スペースキーで浮上
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)|| tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)
		|| tnl::Input::IsPadDownTrigger(ePad::KEY_1)) {

		fish_main_pos_.y -= 2;
		if (accelerate_up_ < -1)accelerate_up_ = -up_power_ren;//連続浮上で少し上昇度up
		else{
		accelerate_up_ = -up_power;  // 上向きの速度
		}

		PlaySoundMem(se_sound, DX_PLAYTYPE_BACK);
	}

	// 速度を位置に加算
	fish_main_pos_.y += accelerate_up_;
	accelerate_up_ += 0.1f;


	//DrawStringEx(800, 500, -1, "%f", accelerate_up_);

	fish_main_pos_.x += accelerate_left_ + accelerate_right_;
	if (accelerate_left_ < -3)accelerate_left_ += 0.2f;
	else if (accelerate_left_ < 0)accelerate_left_ /= 1.2f;
	else accelerate_left_ = 0;//左
	if (accelerate_right_ > 3)accelerate_right_ -= 0.2f;
	else if (accelerate_right_ > 0)accelerate_right_ /= 1.2f;
	else accelerate_right_ = 0;//右
	


	if (fish_main_pos_.y < 0 || fish_main_pos_.y > game_window_height){
		fish_main_pos_.y = prev_main_fish_pos_.y; //画面外に行かせない]
		accelerate_up_ += 0.2f;//画面上部でなかなか降りてこない現象への解決
	}
	if (fish_main_pos_.x < 0 || fish_main_pos_.x > game_window_width) {
		fish_main_pos_.x = prev_main_fish_pos_.x; //画面外に行かせない
	}

	ScenePlay* scene_play =
		static_cast<ScenePlay*>(GameManager::GetInstance()->getSceneInstance());
	//大きさの当たり判定の調整
	if (scene_play->level_ == 2 && !size_resize) {
		fish_main_size_value_ = 1.2f;
		fish_main_size_ *= fish_main_size_value_;
		size_resize = true;
	}
	if (scene_play->level_ == 3 && size_resize) {
		fish_main_size_value_ = 1.2f;
		fish_main_size_ *= fish_main_size_value_;
		size_resize = false;
	}
	if (scene_play->level_ == 4 && !size_resize) {
		fish_main_size_.x = fish_main_size_2_.x * fish_main_size_value_;
		fish_main_size_.y = fish_main_size_2_.y * fish_main_size_value_;
		size_resize = true;
		//highlevel_jadge_ = true;
	}
	if (scene_play->level_ >= 5 && size_resize) {
		fish_main_size_value_ = 1.2f;
		fish_main_size_ *= fish_main_size_value_;
		size_resize = false;
	}
}

void Player::draw() {
	

	if(damaged_judge_) {
		elapsed_ += 1;
		//アニメーション
		if (muki_ == 0)muki_ = 1;
		if (muki_ == 2)muki_ = 3;

		if (!invisible_on_) {
			invisible_ += 25;
			if (invisible_ > 255)invisible_on_ = true;
		}
		else {
			invisible_ -= 25;
			if (invisible_ < 0)invisible_on_ = false;
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, invisible_);

		if (elapsed_ > damaged_time_) {
			damaged_judge_ = false;
			invisible_ = 0;
			invisible_on_ = false;
			elapsed_ = 0;
			if (muki_ == 1)muki_ = 0;
			if (muki_ == 3)muki_ = 2;
		}
	}
	DrawRotaGraph(fish_main_pos_.x, fish_main_pos_.y, fish_main_size_value_, 
		0, fish_main_gfx_[highlevel_jadge_][muki_], true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	//DrawStringEx(400, 50, -1, "%f", fish_main_size_.x);
	//DrawStringEx(400, 100, -1, "%f", fish_main_size_.y);
}