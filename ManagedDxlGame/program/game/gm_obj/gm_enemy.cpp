#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/gm_manager.h"
#include "../scene/gm_scene_play.h"
#include "gm_enemy.h"

//コンストラクタ（最初に一度だけ実行）
Enemy::Enemy() {
	//gm_scene_play.hの変数を扱えます。こちら
	ScenePlay* scene_play = 
		static_cast<ScenePlay*>(GameManager::GetInstance()->getSceneInstance());
	
	if (scene_play->level_ == 1) {
		if (enemy_sort_random_ < 5) {
			LoadDivGraph("graphics/fish1.png",2,1,2,128,128, fish_gfx_);
			enemy_sort_ = fish1;
		}
		else if (enemy_sort_random_ < 7) {
			LoadDivGraph("graphics/fish2.png", 2, 1, 2, 128, 128, fish_gfx_); 
			enemy_sort_ = fish2;
		}
		else {
			LoadDivGraph("graphics/fish3.png", 2, 1, 2, 128, 128, fish_gfx_);
			enemy_sort_ = fish3;
		}
	}
	if (scene_play->level_ == 2) {
		if (enemy_sort_random_ < 3) {
			LoadDivGraph("graphics/fish1.png", 2, 1, 2, 128, 128, fish_gfx_);
			enemy_sort_ = fish1;
		}
		else if (enemy_sort_random_ < 6) {
			LoadDivGraph("graphics/fish2.png", 2, 1, 2, 128, 128, fish_gfx_);
			enemy_sort_ = fish2;
		}
		else if (enemy_sort_random_ < 8) {
			LoadDivGraph("graphics/fish3.png", 2, 1, 2, 128, 128, fish_gfx_); 
			enemy_sort_ = fish3;
		}
		else{
			LoadDivGraph("graphics/fish4.png", 2, 1, 2, 256, 256, fish_gfx_); 
			enemy_sort_ = fish4;
		}
		//level2の時はfish4出る
	}
	if (scene_play->level_ == 3) {
		if (enemy_sort_random_ < 3) {
			LoadDivGraph("graphics/fish2.png", 2, 1, 2, 128, 128, fish_gfx_); 
			enemy_sort_ = fish2;
		}
		else if (enemy_sort_random_ < 6) {
			LoadDivGraph("graphics/fish3.png", 2, 1, 2, 128, 128, fish_gfx_); 
			enemy_sort_ = fish3;
		}
		else if (enemy_sort_random_ < 8) {
			LoadDivGraph("graphics/fish4.png", 2, 1, 2, 256, 256, fish_gfx_); 
			enemy_sort_ = fish4;
		}
		else {
			LoadDivGraph("graphics/fish5.png", 2, 1, 2, 256, 256, fish_gfx_); 
			enemy_sort_ = fish5;
		}
	}
	if (scene_play->level_ == 4) {
		if (enemy_sort_random_ < 3) {
			LoadDivGraph("graphics/fish3.png", 2, 1, 2, 128, 128, fish_gfx_);
			enemy_sort_ = fish3;
		}
		else if (enemy_sort_random_ < 6) {
			LoadDivGraph("graphics/fish4.png", 2, 1, 2, 256, 256, fish_gfx_); 
			enemy_sort_ = fish4;
		}
		else if (enemy_sort_random_ < 8) {
			LoadDivGraph("graphics/fish5.png", 2, 1, 2, 256, 256, fish_gfx_); 
			enemy_sort_ = fish5;
		}
		else {
			LoadDivGraph("graphics/fish6.png", 2, 1, 2, 256, 256, fish_gfx_); 
			enemy_sort_ = fish6;
		}
	}
	if (scene_play->level_ >= 5) {
		if (enemy_sort_random_ < 2) {
			LoadDivGraph("graphics/fish3.png", 2, 1, 2, 128, 128, fish_gfx_); 
			enemy_sort_ = fish3;
		}
		else if (enemy_sort_random_ < 4) {
			LoadDivGraph("graphics/fish4.png", 2, 1, 2, 256, 256, fish_gfx_); 
			enemy_sort_ = fish4;
		}
		else if (enemy_sort_random_ < 6) {
			LoadDivGraph("graphics/fish5.png", 2, 1, 2, 256, 256, fish_gfx_); 
			enemy_sort_ = fish5;
		}
		else {
			LoadDivGraph("graphics/fish6.png", 2, 1, 2, 256, 256, fish_gfx_); 
			enemy_sort_ = fish6;
		}
	}

	//fish_gfx_[fish1] = LoadGraph("graphics/fish4.png");
	//fish_gfx_[fish1] = LoadGraph("graphics/fish5.png");
	if (!muki_dochi)fish_pos_.x = DXE_WINDOW_WIDTH;//初期位置を向きによって調整

	if (enemy_sort_ == fish1) { 
		fish_size_.x = fish1_size_.x;
		fish_size_.y = fish1_size_.y;
	}
	if (enemy_sort_ == fish2) {
		fish_size_.x = fish2_size_.x;
		fish_size_.y = fish2_size_.y;
	}
	if (enemy_sort_ == fish3) {
		fish_size_.x = fish3_size_.x;
		fish_size_.y = fish3_size_.y;
	}
	if (enemy_sort_ == fish4) {
		fish_size_.x = fish4_size_.x;
		fish_size_.y = fish4_size_.y;
	}
	if (enemy_sort_ == fish5) {
		fish_size_.x = fish5_size_.x;
		fish_size_.y = fish5_size_.y;
	}
	if (enemy_sort_ == fish6) {
		fish_size_.x = fish6_size_.x;
		fish_size_.y = fish6_size_.y;
	}
}

// デストラクタ
Enemy::~Enemy() {
	/*delete sceneplay_;
	sceneplay_ = nullptr;*/
	//delete score_;
	//score_ = nullptr;
}


void Enemy::update(float delta_time) {
	ScenePlay* scene_play =
		static_cast<ScenePlay*>(GameManager::GetInstance()->getSceneInstance());
	if (scene_play->level_ == 1 && enemy_sort_ == fish1)feed_judge = true;
	if (scene_play->level_ == 2 && enemy_sort_ <= fish2)feed_judge = true;
	if (scene_play->level_ == 3 && enemy_sort_ <= fish3)feed_judge = true;
	if (scene_play->level_ == 4 && enemy_sort_ <= fish4)feed_judge = true;
	if (scene_play->level_ >= 5 && enemy_sort_ <= fish5)feed_judge = true;

	if (enemy_sort_ == fish1) {
		if (!muki_dochi)fish_pos_.x -= fish1_speed;
		if (muki_dochi)fish_pos_.x += fish1_speed;
	}
	if (enemy_sort_ == fish2) {
		if (!muki_dochi)fish_pos_.x -= fish2_speed;
		if (muki_dochi)fish_pos_.x += fish2_speed;
	}
	if (enemy_sort_ == fish3) {
		if (!muki_dochi)fish_pos_.x -= fish3_speed;
		if (muki_dochi)fish_pos_.x += fish3_speed;
	}
	if (enemy_sort_ == fish4) {
		if (!muki_dochi)fish_pos_.x -= fish4_speed;
		if (muki_dochi)fish_pos_.x += fish4_speed;
	}
	if (enemy_sort_ == fish5) {
		if (!muki_dochi)fish_pos_.x -= fish5_speed;
		if (muki_dochi)fish_pos_.x += fish5_speed;
	}
	if (enemy_sort_ == fish6) {
		if (!muki_dochi)fish_pos_.x -= fish6_speed;
		if (muki_dochi)fish_pos_.x += fish6_speed;
	}
}

void Enemy::draw() {
	DrawRotaGraph(fish_pos_.x, fish_pos_.y, 1.0f, 0, fish_gfx_[muki_dochi], true);

	//DrawStringEx(fish_pos_.x, fish_pos_.y + 20, -1, "%d", fish_size_.x);
	//DrawStringEx(fish_pos_.x, fish_pos_.y + 50, -1, "%d", fish_size_.y);
}