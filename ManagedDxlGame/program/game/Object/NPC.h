#pragma once
///
///NPC�N���X
///

enum  {
	NPC_DIR_DOWN,
	NPC_DIR_UP,
	NPC_DIR_LEFT,
	NPC_DIR_RIGHT,
	NPC_DIR_MAX
};


#include "../dxlib_ext/dxlib_ext.h"
#include"../Manager/Camera.h"

class Npc {
public:

	
	//Npc�̃R���X�g���N�^ : ���� : ( ���O , ���W , �n���h����Pass , �摜�̑傫�� , �ǂ̃A�j���[�V��������n�߂邩, �n���h���̐� )
	Npc(const std::string& name, const tnl::Vector3& pos , std::string ghdl_pass[], float scale , int animation_namber , int ghdl_num);
	void ChengeAnimation();

	void Update(float delta_time);
	void Draw(const Camera_& camera);

	std::string npc_name_;							//npc�̖��O
	int  npc_ghdl;									//npc�̉摜
	tnl::Vector3 npc_pos_ = {};					    //npc�̍��W
	int NpcCharaChipWidth  = 48;					//Npc�̃L�����`�b�v�̕�
	int NpcCharaChipHeight = 48;					//Npc�̃L�����`�b�v�̍���


//------------------------------------------------------------------------------------------------------------------------
//�A�j���[�V����


	int animation_select = 0;						//Npc�̃A�j���[�V������؂�ւ���
	
private:

	float scale_ = 0;								//���ꂼ��̉摜�Ŏg���傫�������߂�
	float anim_time_count = 0;						//�A�j���[�V�����̃J�E���g
	int anim_ctrl_dir = NPC_DIR_DOWN;				//�A�j���[�V�����̑I��
	int anim_ctrl_frame = 0;						//�t���[��
	int anim_hdls[NPC_DIR_MAX][5];					//�A�j���[�V�����̔z��


};