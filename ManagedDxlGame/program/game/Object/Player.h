#pragma once
///
///�v���C���[�Ɋւ���N���X
/// 


#include "../dxlib_ext/dxlib_ext.h"
#include"Actor.h"
#include"../Manager/Camera.h"

class Actor;

enum {
	DIR_DOWN,
	DIR_UP,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_MAX
};

class Player : public Actor{
public:

	/*Player();*/
	Player( float Hp, int Attack, int Defence);

	tnl::Vector3 plyer_pos = {};
	float first_pos_x = 195;						//�Q�[�����n�܂������̂����W
	float first_pos_y = 312;						//�Q�[�����n�܂�������y���W
	int Total_Frame = 3;							//�v���C���[�̑��t���[��(3)
	int Horizontal_frame = 3;						//�v���C���[�̉��t���[��(3)
	int Vertical_frame = 1;							//�v���C���[�̏c�t���[��(1)
	int Horizontal_oneframe = 32;					//�������� 1�t���[��������̕�(64)
	int Vertical_oneframe = 32;						//�c������ 1�t���[��������̕�(64)



	const int CHARA_HEIGHT = 64;					//�v���C���[�̍���
	const int CHARA_WIDTH = 64;						//�v���C���[�̕�

	void Update(float delta_time);

	//�v���C���[�̓���
	void player_Move(float delta_time);
	//�v���C���[�̕`��
	void player_draw(const Camera_& camera);

private:
	

	//�A�j���[�V�����Ɏg���ϐ�
	float anim_time_count = 0;
	int anim_ctrl_dir = DIR_DOWN;
	int anim_ctrl_frame = 0;
	int anim_hdls[DIR_MAX][5];

	//plyer�̕���
	float numberStep = 0;

};

