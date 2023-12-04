#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/gm_manager.h"
#include "../scene/gm_scene_play.h"
#include "gm_player.h"

//�R���X�g���N�^�i�ŏ��Ɉ�x�������s�j
Player::Player() {
	//fish_main_gfx_ = LoadGraph("graphics/fish_main.png");
	LoadDivGraph(
			"graphics/fish_main.png",//�摜�̃p�X
			4,								//���t���[����
			2,								//���t���[����
			2,								//�c�t���[����
			128,								//�������� 1�t���[��������̕�
			128,								//�c������ 1�t���[��������̕�
			fish_main_gfx_[0]);						//�摜�n���h�����i�[����z��

	LoadDivGraph("graphics/fish_main2.png", 4, 2, 2, 256, 256, fish_main_gfx_[1]);
		se_sound = LoadSoundMem("sound/se/jump.mp3");
}

// �f�X�g���N�^
Player::~Player() {

}


void Player::update(float delta_time) {

	tnl::Vector3 prev_main_fish_pos_ = fish_main_pos_;
	//float prev_accelerate_up = accelerate_up_;
		// �����L�[�ō��E�Ɉړ�
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

	// �X�y�[�X�L�[�ŕ���
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)|| tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)
		|| tnl::Input::IsPadDownTrigger(ePad::KEY_1)) {

		fish_main_pos_.y -= 2;
		if (accelerate_up_ < -1)accelerate_up_ = -up_power_ren;//�A������ŏ����㏸�xup
		else{
		accelerate_up_ = -up_power;  // ������̑��x
		}

		PlaySoundMem(se_sound, DX_PLAYTYPE_BACK);
	}

	// ���x���ʒu�ɉ��Z
	fish_main_pos_.y += accelerate_up_;
	accelerate_up_ += 0.1f;


	//DrawStringEx(800, 500, -1, "%f", accelerate_up_);

	fish_main_pos_.x += accelerate_left_ + accelerate_right_;
	if (accelerate_left_ < -3)accelerate_left_ += 0.2f;
	else if (accelerate_left_ < 0)accelerate_left_ /= 1.2f;
	else accelerate_left_ = 0;//��
	if (accelerate_right_ > 3)accelerate_right_ -= 0.2f;
	else if (accelerate_right_ > 0)accelerate_right_ /= 1.2f;
	else accelerate_right_ = 0;//�E
	


	if (fish_main_pos_.y < 0 || fish_main_pos_.y > game_window_height){
		fish_main_pos_.y = prev_main_fish_pos_.y; //��ʊO�ɍs�����Ȃ�]
		accelerate_up_ += 0.2f;//��ʏ㕔�łȂ��Ȃ��~��Ă��Ȃ����ۂւ̉���
	}
	if (fish_main_pos_.x < 0 || fish_main_pos_.x > game_window_width) {
		fish_main_pos_.x = prev_main_fish_pos_.x; //��ʊO�ɍs�����Ȃ�
	}

	ScenePlay* scene_play =
		static_cast<ScenePlay*>(GameManager::GetInstance()->getSceneInstance());
	//�傫���̓����蔻��̒���
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
		//�A�j���[�V����
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