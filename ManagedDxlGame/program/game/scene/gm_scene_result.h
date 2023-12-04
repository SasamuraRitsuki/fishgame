#pragma once
#include "../common/gm_scene_base.h"

class SceneResult : public SceneBase {
public:
	SceneResult(int score = 0,int highscore = 0);

	void update(float delta_time) override;
	void draw() override;

	int finalscore_ = 0;

	int GetScore() const { return finalscore_; }
	void SetScore(int a) { highscore_ = a; }

	int highscore_ = 0;
private:
	tnl::Sequence<SceneResult> sequence_ = tnl::Sequence<SceneResult>(this, &SceneResult::seqIdle);
	bool seqIdle(float delta_time);

	int back_ground_gfx_ = 0;
	int se_sound[3];
	float elapsed_ = 0;
	int count_scene = 0;
	int enter_gfx_;
	tnl::Vector3 text_pos_ = { 400,200,0 };
	tnl::Vector3 score_pos_ = { DXE_WINDOW_WIDTH / 2 - 100,DXE_WINDOW_HEIGHT / 2 - 50 ,0 };
	tnl::Vector3 highscore_pos_ = { 100,DXE_WINDOW_HEIGHT / 2 + 100 ,0 };
	tnl::Vector3 enter_pos_ = { DXE_WINDOW_WIDTH / 2,DXE_WINDOW_HEIGHT / 2 + 200,0 };
	bool enter_on = false;
};

