//
//���N���X�i��ɉ����̑������̃N���X�ŊǗ�����j
//


#pragma once
#include"../Scene/BaseScene.h"
#include "../dxlib_ext/dxlib_ext.h"
#include"../Map/Mapchip.h"
#include"../Manager/Camera.h"
#include"../Object/Player.h"


class VillageScene : public BaseScene {
public:
	VillageScene();

	void Update(float delta_time)override;
	void Draw()override;

	std::list<MapChip*> MapChips;
	std::vector<std::vector<int>> map_csv;								//mapChip���i�[����ꏊ

private:
	tnl::Sequence<VillageScene> sequence_ = tnl::Sequence<VillageScene>(this, &VillageScene::seqIdle);
	bool seqIdle(float delta_time);

	void mapChip_Loding();												//mapChip�̓ǂݍ��݊֐�
	void mapChip_collision();											//mapChip�̂����蔻��֐�

	std::string gpc_map_chip_hdls_pass_;								// �摜�p�X
	int map_chip_width_;												// �}�b�v�`�b�v�̕�
	int map_chip_height_;												// �}�b�v�`�b�v�̍���
	int map_chip_all_size_;												// �}�b�v�`�b�v�̑��t���[����
	int map_chip_x_size_;												// �}�b�v�`�b�v�̉��t���[����
	int map_chip_y_size_;												// �}�b�v�`�b�v�̏c�t���[����
	int* gpc_map_chip_hdls_;											// �摜�f�[�^�i�[
	std::string map_data_csv_pass_;										// �}�b�vCSV�f�[�^�̃p�X

	


	//villageMap�Ŏg���|�C���^
	Shared<Camera_>camera = nullptr;
	Shared<Player>my_player = nullptr;

};