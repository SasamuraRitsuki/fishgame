#pragma once
#include "../gm_obj/gm_score.h"

class Enemy {
public:
	Enemy();
	~Enemy();
	void update(float delta_time);
	void draw();

	//tnl::Vector3 get_fish_pos_() const { return fish_pos_; }
	//tnl::Vector3 get_fish_size_() const { return fish_pos_; }
	//tnl::Vector3 fish_pos_ = { 0, rand() % 600 + 80,0 };
	tnl::Vector3 fish_pos_ = { 0,static_cast<float>(rand() % 550 + 50),0 };
	tnl::Vector3 fish_size_= { 0,0,0 };//横、縦
	tnl::Vector3 fish1_size_ = { 96,48,0 };
	tnl::Vector3 fish2_size_ = { 96,72,0 };
	tnl::Vector3 fish3_size_ = { 120,64,0 };
	tnl::Vector3 fish4_size_ = { 160,72,0 };
	tnl::Vector3 fish5_size_ = { 168,72,0 };
	tnl::Vector3 fish6_size_ = { 160,80,0 };

	//int get_sort_() { return enemy_sort_; }

	int enemy_sort_ = 100;
	bool feed_judge = false;//食べることが出来るかどうか


	enum {
		fish1, fish2, fish3, fish4, fish5, fish6
	};
	enum {
		left,right
	};
	int level_ = 1;

private:
	//Score* score_ = nullptr;

	
	//ScenePlay* sceneplay_ = nullptr;

	bool muki_dochi = rand() % 2;
	//0が左。
	int enemy_sort_random_ = rand() % 9;
	int fish_gfx_[2];
	float fish1_speed = 6;//fish1のスピード
	float fish2_speed = 6.5f;
	float fish3_speed = 7.5f;
	float fish4_speed = 8;
	float fish5_speed = 6;
	float fish6_speed = 9 + rand() % 4;
};