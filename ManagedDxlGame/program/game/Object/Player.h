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

class Player : public Actor {
public:

	
	Player();

	void Update(float delta_time);


	//---�v���C���[�֌W---//
	tnl::Vector3 plyer_pos = {};
	float first_pos_x = 195;						//�Q�[�����n�܂������̂����W
	float first_pos_y = 312;						//�Q�[�����n�܂�������y���W
	int Total_Frame = 3;							//�v���C���[�̑��t���[��(3)
	int Horizontal_frame = 3;						//�v���C���[�̉��t���[��(3)
	int Vertical_frame = 1;							//�v���C���[�̏c�t���[��(1)
	int Horizontal_oneframe = 32;					//�������� 1�t���[��������̕�(32)
	int Vertical_oneframe = 32;						//�c������ 1�t���[��������̕�(32)

	//plyer�̕���
	float numberStep = 0;
	//plyer�̓����̐���
	bool plyControl = true;

	//player�̈ړ��O���W
	tnl::Vector3 prev_pos = { 0 ,0,0 };


	const int CHARA_HEIGHT = 48;					//�v���C���[�̍���
	const int CHARA_WIDTH = 48;						//�v���C���[�̕�

	//�v���C���[�̂���
	int money = 0;

	//�v���C���[�̍ő�HP
	int MaxHp = 0;

	//�v���C���[�̓���
	void player_Move(float delta_time , const float& velocity);
	//�v���C���[�̕`��
	void player_draw(const Camera_& camera, float scale);
	
	tnl::Vector3 SetAndGetPlayerPosition(const tnl::Vector3& new_pos) {
		plyer_pos = new_pos;
		return plyer_pos;
	}

	//�v���C���[�̃X�e�[�^�X�����[�h����
	void PlyStatusLoad();

	//�v���C���[��MaxHp�̍X�V����
	int PlyerMaxHp(int id);

	//plyer�̃X�e�[�^�X
	typedef struct {
		int id;
		int hp;
		int Attack;
		int Defance;
		int Speed;
		int R_expoint;
		int level;
	}PlyerStatus;

	//�Z�[�u���鎞�Ɏg���z��
	std::vector<PlyerStatus>plyerstatusSave;
	

private:
	

	//�A�j���[�V�����Ɏg���ϐ�
	float anim_time_count = 0;
	int anim_ctrl_dir = DIR_DOWN;
	int anim_ctrl_frame = 0;
	int anim_hdls[DIR_MAX][5];

	//plyer�̃X�e�[�^�X���Ǘ�����


	//Status������ϐ�
	PlyerStatus plyer_Status;

	//�\���̂̑���
	int Ply_Status_Total_num;

	//�\���̂��i�[����z��
	std::list<PlyerStatus>Ply_Status_Type;

	//csv�ǂݎ��p�̔z��
	std::vector<std::vector<tnl::CsvCell>>PlyerStatus_Csv_Info;

	//�X�e�[�^�X���Ǘ����邽�߂�ID
	int PlyerId = 1;

public:

	//�v���C���[�̃X�e�[�^�X�𑼂̃N���X�ȂǂŎ擾����
	PlyerStatus GetPlyerStatus(int id) const {
		auto it = std::find_if(Ply_Status_Type.begin(), Ply_Status_Type.end(), [id]
		(const PlyerStatus& status) {return status.id == id; });

		if (it != Ply_Status_Type.end()) {
			return *it;
		}
		else {
			// ID�ɑΉ�����A�C�e����������Ȃ��ꍇ�́A�K���ȃf�t�H���g�l��Ԃ����G���[�������s���Ȃ�
			return PlyerStatus{};
		}

	}

	int GetPlayerId() {
		return PlyerId;
	}

	void PlyerSave();
	void PlyerLoad();


};

