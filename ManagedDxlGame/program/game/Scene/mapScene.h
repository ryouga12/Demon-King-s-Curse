///
///WorldMap�N���X
//

#pragma once
#include	<unordered_set>
#include"../Scene/BaseScene.h"
#include "../dxlib_ext/dxlib_ext.h"
#include"../Map/Mapchip.h"
#include"../Manager/Camera.h"
#include"../Object/Player.h"
#include"../Item/Weapon.h"
#include"../Item/Item.h"
#include"../Manager/GameManager.h"
#include"../Scene/village.h"
#include"../Item/Inventory.h"
#include"../Item/WeaponShop.h"



class MapScene : public BaseScene {
public:
	MapScene(tnl::Vector3 PlyerPos, Shared<Inventory>inventory);

	void Update(float delta_time)override;
	void Draw()override;

	

	
private:

	void worldMapLoad();

	tnl::Vector3 pos = { 0 , 0 , 0 };

	//��ڂ̑��ɓ��������̍��W
	/*tnl::Vector3 village_Pos = { 0 , 500 , 0 };*/

	

//------------------------------------------------------------------------------------------------------------------------
//�V�[�P���X

	tnl::Sequence<MapScene> sequence_ = tnl::Sequence<MapScene>(this, &MapScene::seqIdle);
	bool seqIdle(float delta_time);
	//�V�[����ς���ׂ̃V�[�P���X
	bool seqChangeScene(float delta_time) { return true; }
	
		
//------------------------------------------------------------------------------------------------------------------------
//---����֌W---//
	std::vector<ItemBase>weapons;



//--------------------------------------------------------------------------------------------------------------------------
//�|�C���^�ϐ�
//

	Shared<Camera_>camera = nullptr;
	Shared<Player>myPlayer = nullptr;
	Shared<MapChip>mapchip = nullptr;
	Shared<GameManager>gmanager = nullptr;
	Shared<VillageScene>villageScene = nullptr;
	Shared<Inventory>inventory_ = nullptr;


//--------------------------------------------------------------------------------------------------------------------------
//mapchip�֘A
//

	std::string map_chip_ghdl_pass;
	//������csv��data��pass
	std::string map_chip_csv_pass;
	//������؂Ȃǂ̃I�u�W�F�N�g�p��csv��datapass
	std::string map_chip_csv_object_pass;


	//csv��mapchip���i�[����z��
	std::vector<std::vector<int>>world_map_csv;

	std::vector<std::vector<int>>world_object_csv;

	std::list<MapChip*>MapChips_object;

	std::list<MapChip*>MapChip_continent;

	// �}�b�v�`�b�v�̕�
	int map_chip_width_;	
	// �}�b�v�`�b�v�̍���
	int map_chip_height_;	
	// �}�b�v�`�b�v�̑��t���[����
	int map_chip_all_size_;	
	// �}�b�v�`�b�v�̉��t���[����
	int map_chip_x_size_;
	//mapchip�̏c�t���[����
	int map_chip_y_size_;

	int* gpc_map_chip_hdls_;

	int MAP_HEIGHT = 3200;
	int MAP_WIDTH  = 6400;

	//���̒��̒l�œ����蔻������߂�
	std::unordered_set<int> colisionObjectValues = { 10 , 11 ,12, 13 , 18 , 19, 20 , 21 ,25, 36 , 37  ,41 , 234  ,335,432,440,442  , 827 , 835 ,1302,1303, 1336, 1337, 1363 ,1364 ,1365, 1476, 1477, 2024 };

	//���Ȃǂ̓����蔻��Ɏg���l
	std::unordered_set<int>villageValues = { 334 , 2032 , 2033  , 2034 , 2035 , 2069,2089,2090 };

	//�n�`�Ŏg�������蔻��̒l
	std::unordered_set<int>worldCollisionValues = {2024 , 2027};


	void WorldMapCollision();

};