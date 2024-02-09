///
///WorldMapクラス
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

	//一個目の村に入った時の座標
	/*tnl::Vector3 village_Pos = { 0 , 500 , 0 };*/

	

//------------------------------------------------------------------------------------------------------------------------
//シーケンス

	tnl::Sequence<MapScene> sequence_ = tnl::Sequence<MapScene>(this, &MapScene::seqIdle);
	bool seqIdle(float delta_time);
	//シーンを変える為のシーケンス
	bool seqChangeScene(float delta_time) { return true; }
	
		
//------------------------------------------------------------------------------------------------------------------------
//---武器関係---//
	std::vector<ItemBase>weapons;



//--------------------------------------------------------------------------------------------------------------------------
//ポインタ変数
//

	Shared<Camera_>camera = nullptr;
	Shared<Player>myPlayer = nullptr;
	Shared<MapChip>mapchip = nullptr;
	Shared<GameManager>gmanager = nullptr;
	Shared<VillageScene>villageScene = nullptr;
	Shared<Inventory>inventory_ = nullptr;


//--------------------------------------------------------------------------------------------------------------------------
//mapchip関連
//

	std::string map_chip_ghdl_pass;
	//平原のcsvのdataのpass
	std::string map_chip_csv_pass;
	//建物や木などのオブジェクト用のcsvのdatapass
	std::string map_chip_csv_object_pass;


	//csvのmapchipを格納する配列
	std::vector<std::vector<int>>world_map_csv;

	std::vector<std::vector<int>>world_object_csv;

	std::list<MapChip*>MapChips_object;

	std::list<MapChip*>MapChip_continent;

	// マップチップの幅
	int map_chip_width_;	
	// マップチップの高さ
	int map_chip_height_;	
	// マップチップの総フレーム数
	int map_chip_all_size_;	
	// マップチップの横フレーム数
	int map_chip_x_size_;
	//mapchipの縦フレーム数
	int map_chip_y_size_;

	int* gpc_map_chip_hdls_;

	int MAP_HEIGHT = 3200;
	int MAP_WIDTH  = 6400;

	//この中の値で当たり判定をきめる
	std::unordered_set<int> colisionObjectValues = { 10 , 11 ,12, 13 , 18 , 19, 20 , 21 ,25, 36 , 37  ,41 , 234  ,335,432,440,442  , 827 , 835 ,1302,1303, 1336, 1337, 1363 ,1364 ,1365, 1476, 1477, 2024 };

	//町などの当たり判定に使う値
	std::unordered_set<int>villageValues = { 334 , 2032 , 2033  , 2034 , 2035 , 2069,2089,2090 };

	//地形で使う当たり判定の値
	std::unordered_set<int>worldCollisionValues = {2024 , 2027};


	void WorldMapCollision();

};