#pragma once
#include "../common/gm_scene_base.h"

class SceneTitle : public SceneBase {
public :
	void update(float delta_time) override ;
	void draw() override;

	SceneTitle();
private :
	tnl::Sequence<SceneTitle> sequence_ = tnl::Sequence<SceneTitle>(this, &SceneTitle::seqIdle);
	bool seqIdle(float delta_time) ;

	int back_ground_gfx_;
	int enter_gfx_;
	int menu_sound;
	int se_sound;
	int se_hdl[10] = { 0 };
	tnl::Vector3 enter_pos_ = { 885,520,0 };
	float elapsed_ = 0;
	bool enter_on = false;
};

