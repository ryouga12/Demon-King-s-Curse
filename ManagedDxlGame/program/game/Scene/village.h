//
//���N���X�i��ɉ����̑������̃N���X�ŊǗ�����\��j
//


#pragma once
#include	<unordered_set>
#include"../Scene/BaseScene.h"
#include "../dxlib_ext/dxlib_ext.h"
#include"../Map/Mapchip.h"
#include"../Manager/Camera.h"
#include"../Object/Player.h"
#include"../Manager/GameManager.h"
#include"../Menu/MenuWindow.h"
#include"../Item/Weapon.h"
#include"../Manager/SystemManager.h"
#include"../Object/NPC.h"
#include"../Item/WeaponShop.h"



class VillageScene : public BaseScene {
public:
	
	VillageScene();
	~VillageScene();

	void Update(float delta_time)override;
	void Draw()override;
	void InitVillageScene();

	


//------------------------------------------------------------------------------------------------------------------------
//MapChip�֘A

	//mapChip���i�[����ꏊ
	std::list<MapChip*> MapChips;
	std::vector<std::vector<int>> map_csv;								
	
	//---�`�悷��ۂ̃t���O---//
	bool drawWindowFlag = true;
	bool drawSeqFlag = false;

private:
	/*TNL_CO_SEQUENCE(VillageScene , &VillageScene::seqIdle)*/

	//---mapChip�֘A�̏���---//
	void mapChip_Loding();												//mapChip�̓ǂݍ��݊֐�
	void mapChip_collision();											//mapChip�̂����蔻��֐�
	
	//---mapChip�֘A�̕ϐ�---//
	std::string gpc_map_chip_hdls_pass_;								// �摜�p�X
	int map_chip_width_;												// �}�b�v�`�b�v�̕�
	int map_chip_height_;												// �}�b�v�`�b�v�̍���
	int map_chip_all_size_;												// �}�b�v�`�b�v�̑��t���[����
	int map_chip_x_size_;												// �}�b�v�`�b�v�̉��t���[����
	int map_chip_y_size_;												// �}�b�v�`�b�v�̏c�t���[����
	int* gpc_map_chip_hdls_;											// �摜�f�[�^�i�[
	std::string map_data_csv_pass_;										// �}�b�vCSV�f�[�^�̃p�X
	int MAP_HEIGHT = 960;												//�}�b�v�̍���
	int MAP_WIDTH = 1600;												//�}�b�v�̕�

	tnl::Vector3 first_pos  = { 195, 312 , 0 };							//�����ʒu
	tnl::Vector3 first_world_pos = { 435 , 1770 , 0 };					//worldMap�ł̍ŏ��̈ʒu

	// ---���̔z��̒��ɓ����Ă���l���g���Ă����蔻������߂�---//
	std::unordered_set<int> colisionValues = {-1, 324, 384, 392, 545, 528, 536, 464, 631, 708, 614, 630, 510, 400, 408, 657, 656, 395, 230, 231};
		
//------------------------------------------------------------------------------------------------------------------------
//---�|�C���^---//

	Shared<Camera_>camera = nullptr;
	Shared<Player>my_player = nullptr;
	GameManager* gmanager = nullptr;
	Shared<Menu>menuWindow = nullptr;
	Shared<Menu>menuSelectWindow = nullptr;
	Shared<Menu>menuComentWindiow = nullptr;
	Shared<Menu>menu_Back_Window = nullptr;
	Shared<Weapon>weapon = nullptr;
	///*MenuWindow* use_equip = nullptr;*/
	Shared<SystemManager>systemManager = nullptr;
	Shared<Npc>herdman_npc = nullptr;
	Shared<Npc>Armsdealer_npc = nullptr;
	Shared<Npc>Priest_npc = nullptr;
	Shared<WeaponShop>weapon_shop = nullptr;
	Shared<Inventory>inventory_ = nullptr;
	

//------------------------------------------------------------------------------------------------------------------------
//---�V�[�P���X---//

	//�V�[�P���X���Ǘ�����N���X
	enum class Sequence_num {
		Idle,
		WeaponShop,
		Inventory,
		MenuOpen,
		MenuShopOpen,
		MenuNpc
	};

	//�ǂ̃V�[�P���X���I������Ă��邩
	 Sequence_num select_num;

	//�V�[�P���X�̒�`
	tnl::Sequence<VillageScene> sequence_ = tnl::Sequence<VillageScene>(this, &VillageScene::seqIdle);

	//�ʏ펞�̃V�[�P���X
	bool seqIdle(float delta_time);

	//�C���x���g���̃V�[�P���X
	bool seqInventory(float delta_time);

	//���퉮�̃V�[�P���X
	bool seqWeaponShop(float delta_time);

	//���j���[�V�[�P���X
	bool seqMenuOpen(float delta_time);

	//�V�[����ς���ׂ̃V�[�P���X
	bool seqChangeScene(float delta_time);

	//Npc�̃V�[�P���X
	bool seqNpc(float delta_time);

//------------------------------------------------------------------------------------------------------------------------
//---����֌W---//
	std::vector<ItemBase> weapon_List;
	

//------------------------------------------------------------------------------------------------------------------------
//---���j���[�֌W---//
public:
	

private:
	/*int id;
	int CursourPosY;*/
	//���j���[�I���Ŏg���|�C���^(�\����)
	/*MenuWindow::MenuElement_t* menu_usable = nullptr;*/

	//���j���[�̎g������
	enum class MenuOpenNum {
		WeaponShop,			//���퉮
		Herdman,			//����
		Priest,				//�_��
		Object				//�I�u�W�F�N�g
	};

	//�ǂ̃��j���[���J���Ă��邩
	 MenuOpenNum select_menu_num;

	//���j���[��ʂŕ\������A�C�R���I�Ȃ���
	int Armsdealer_icon_hdl = 0;	
	int herdman_icon_hdl = 0;
	int Priest_icon_hdl = 0;
	int Player_icon_hdl = 0;

//------------------------------------------------------------------------------------------------------------------------
//---Npc�֌W---//				
	std::string herdman_hdl_pass[4] = {"graphics/Npc/herdman.png" ,"graphics/Npc/herdman_idle.png" ,"graphics/Npc/herdman_right.png","graphics/Npc/herdman_up.png" };
	std::string Armsdealer_hdl_pass[1] = {"graphics/Npc/Armsdealer.png"};
	std::string Priest_hdl_pass[3] = {"graphics/Npc/Priest_npc.png" , "graphics/Npc/Priest_left.png" , "graphics/Npc/Priest_right.png" };

	//Npc�ɂ���ē����ς���
	enum class NpcMove {
		Empty,				//��
		Herdman,			//����
		Priest				//�_��
	};

	//�N��������s����
	NpcMove npcMove = NpcMove::Empty;

public:

	//inventory
	Shared<Inventory> GetInventory() { return inventory_; }

};