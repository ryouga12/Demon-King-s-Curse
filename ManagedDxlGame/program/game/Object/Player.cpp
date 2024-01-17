#include "Player.h"
#include"../Manager/Camera.h"

Player::Player(float Hp, int Attack, int Defence)
{
	name = "Player";
	
	hp = baseHp;
	attack = baseAttack;
	defance = baseDefance;

	//�A�j���[�V�����̃��[�h����
	std::string files[DIR_MAX] = {
		"graphics/Player/pipo-charachip_Idle.png",
		"graphics/Player/pipo-charachip_UP.png",
		"graphics/Player/pipo-charachip_Left.png",
		"graphics/Player/pipo-charachip_Right.png"
		
	};

	for (int i = 0; i < 4; i++) {
		LoadDivGraph(
			files[i].c_str(),				// �摜�̃p�X
			Total_Frame,					// ���t���[����
			Horizontal_frame,				// ���t���[����
			Vertical_frame,					// �c�t���[����
			Horizontal_oneframe,			// �������� 1�t���[��������̕�
			Vertical_oneframe,				// �c������ 1�t���[��������̕�
			anim_hdls[i]);					// �摜�n���h�����i�[����z��);
	}

	//�v���C���[�̍��W�̏�����
	plyer_pos = { first_pos_x, first_pos_y , 0 };
}

void Player::Update(float delta_time)
{

}

void Player::player_Move(float delta_time)
{

	//�A�j���[�V����
	anim_time_count += delta_time;
	if (anim_time_count > 0.1f) {
		anim_ctrl_frame++;
		anim_ctrl_frame %= 3;

		anim_time_count = 0;
	}


	if (tnl::Input::IsKeyDown(eKeys::KB_A)) {
		plyer_pos.x -= 5;
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
		plyer_pos.x += 5;
	}

	if (tnl::Input::IsKeyDown(eKeys::KB_W)) {
		plyer_pos.y -= 5;
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_S)) {
		plyer_pos.y += 5;
	}

	//�A�j���[�V�����̓���
	if (tnl::Input::IsKeyDown(eKeys::KB_W))    anim_ctrl_dir = DIR_UP;
	if (tnl::Input::IsKeyDown(eKeys::KB_S))    anim_ctrl_dir = DIR_DOWN;
	if (tnl::Input::IsKeyDown(eKeys::KB_A))	   anim_ctrl_dir = DIR_LEFT;
	if (tnl::Input::IsKeyDown(eKeys::KB_D))    anim_ctrl_dir = DIR_RIGHT;

}

void Player::player_draw(const Camera_& camera)
{
	tnl::Vector3 draw_pos = plyer_pos - camera.target_ + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
	DrawRotaGraph(draw_pos.x, draw_pos.y, 1.5f, 0, anim_hdls[anim_ctrl_dir][anim_ctrl_frame], true);

}


