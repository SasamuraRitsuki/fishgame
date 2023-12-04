#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_scene_title.h"
#include "gm_scene_play.h"
#include "../common/gm_manager.h"

SceneTitle::SceneTitle() {

}

void SceneTitle::update(float delta_time) {
	sequence_.update(delta_time);
	elapsed_ += delta_time;
	if (elapsed_ > 1 && enter_on) {
		enter_on = false;
		elapsed_ = 0;
	}
	else if (elapsed_ > 1) {
		enter_on = true;
		elapsed_ = 0;
	}
	
}

void SceneTitle::draw() {
	DrawRotaGraph( DXE_WINDOW_WIDTH/2, DXE_WINDOW_HEIGHT / 2, 1.0f, 0, back_ground_gfx_, false);
	if(enter_on)DrawRotaGraph(enter_pos_.x, enter_pos_.y, 1.0f, 0, enter_gfx_, true);
}

bool SceneTitle::seqIdle(float delta_time) {
	if (sequence_.isStart()) {
		back_ground_gfx_ = LoadGraph("graphics/title.png");
		enter_gfx_ = LoadGraph("graphics/enter.png");
		menu_sound = LoadSoundMem("sound/menu.mp3");
		se_sound = LoadSoundMem("sound/se/idou_button.mp3");
		PlaySoundMem(menu_sound, DX_PLAYTYPE_LOOP);
		//int SetVolumeMusic(0);
	}

	if ((tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) )|| 
		(tnl::Input::IsPadDownTrigger(ePad::KEY_1)) ){
		StopSoundMem(menu_sound);
		PlaySoundMem(se_sound, DX_PLAYTYPE_BACK);
		auto mgr = GameManager::GetInstance();
		mgr->changeScene(new ScenePlay());
	}
	return true;
}