//
//村クラス（主に何個かの村をこのクラスで管理する）
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
	std::vector<std::vector<int>> map_csv;								//mapChipを格納する場所

private:
	tnl::Sequence<VillageScene> sequence_ = tnl::Sequence<VillageScene>(this, &VillageScene::seqIdle);
	bool seqIdle(float delta_time);

	void mapChip_Loding();												//mapChipの読み込み関数
	void mapChip_collision();											//mapChipのあたり判定関数

	std::string gpc_map_chip_hdls_pass_;								// 画像パス
	int map_chip_width_;												// マップチップの幅
	int map_chip_height_;												// マップチップの高さ
	int map_chip_all_size_;												// マップチップの総フレーム数
	int map_chip_x_size_;												// マップチップの横フレーム数
	int map_chip_y_size_;												// マップチップの縦フレーム数
	int* gpc_map_chip_hdls_;											// 画像データ格納
	std::string map_data_csv_pass_;										// マップCSVデータのパス

	


	//villageMapで使うポインタ
	Shared<Camera_>camera = nullptr;
	Shared<Player>my_player = nullptr;

};