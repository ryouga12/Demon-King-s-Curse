//
//村クラス（主に何個かの村をこのクラスで管理する予定）
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
//MapChip関連

	//mapChipを格納する場所
	std::list<MapChip*> MapChips;
	std::vector<std::vector<int>> map_csv;								
	
	//---描画する際のフラグ---//
	bool drawWindowFlag = true;
	bool drawSeqFlag = false;

private:
	/*TNL_CO_SEQUENCE(VillageScene , &VillageScene::seqIdle)*/

	//---mapChip関連の処理---//
	void mapChip_Loding();												//mapChipの読み込み関数
	void mapChip_collision();											//mapChipのあたり判定関数
	
	//---mapChip関連の変数---//
	std::string gpc_map_chip_hdls_pass_;								// 画像パス
	int map_chip_width_;												// マップチップの幅
	int map_chip_height_;												// マップチップの高さ
	int map_chip_all_size_;												// マップチップの総フレーム数
	int map_chip_x_size_;												// マップチップの横フレーム数
	int map_chip_y_size_;												// マップチップの縦フレーム数
	int* gpc_map_chip_hdls_;											// 画像データ格納
	std::string map_data_csv_pass_;										// マップCSVデータのパス
	int MAP_HEIGHT = 960;												//マップの高さ
	int MAP_WIDTH = 1600;												//マップの幅

	tnl::Vector3 first_pos  = { 195, 312 , 0 };							//初期位置
	tnl::Vector3 first_world_pos = { 435 , 1770 , 0 };					//worldMapでの最初の位置

	// ---この配列の中に入っている値を使ってあたり判定を決める---//
	std::unordered_set<int> colisionValues = {-1, 324, 384, 392, 545, 528, 536, 464, 631, 708, 614, 630, 510, 400, 408, 657, 656, 395, 230, 231};
		
//------------------------------------------------------------------------------------------------------------------------
//---ポインタ---//

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
//---シーケンス---//

	//シーケンスを管理するクラス
	enum class Sequence_num {
		Idle,
		WeaponShop,
		Inventory,
		MenuOpen,
		MenuShopOpen,
		MenuNpc
	};

	//どのシーケンスが選択されているか
	 Sequence_num select_num;

	//シーケンスの定義
	tnl::Sequence<VillageScene> sequence_ = tnl::Sequence<VillageScene>(this, &VillageScene::seqIdle);

	//通常時のシーケンス
	bool seqIdle(float delta_time);

	//インベントリのシーケンス
	bool seqInventory(float delta_time);

	//武器屋のシーケンス
	bool seqWeaponShop(float delta_time);

	//メニューシーケンス
	bool seqMenuOpen(float delta_time);

	//シーンを変える為のシーケンス
	bool seqChangeScene(float delta_time);

	//Npcのシーケンス
	bool seqNpc(float delta_time);

//------------------------------------------------------------------------------------------------------------------------
//---武器関係---//
	std::vector<ItemBase> weapon_List;
	

//------------------------------------------------------------------------------------------------------------------------
//---メニュー関係---//
public:
	

private:
	/*int id;
	int CursourPosY;*/
	//メニュー選択で使うポインタ(構造体)
	/*MenuWindow::MenuElement_t* menu_usable = nullptr;*/

	//メニューの使い分け
	enum class MenuOpenNum {
		WeaponShop,			//武器屋
		Herdman,			//村長
		Priest,				//神官
		Object				//オブジェクト
	};

	//どのメニューを開いているか
	 MenuOpenNum select_menu_num;

	//メニュー画面で表示するアイコン的なもの
	int Armsdealer_icon_hdl = 0;	
	int herdman_icon_hdl = 0;
	int Priest_icon_hdl = 0;
	int Player_icon_hdl = 0;

//------------------------------------------------------------------------------------------------------------------------
//---Npc関係---//				
	std::string herdman_hdl_pass[4] = {"graphics/Npc/herdman.png" ,"graphics/Npc/herdman_idle.png" ,"graphics/Npc/herdman_right.png","graphics/Npc/herdman_up.png" };
	std::string Armsdealer_hdl_pass[1] = {"graphics/Npc/Armsdealer.png"};
	std::string Priest_hdl_pass[3] = {"graphics/Npc/Priest_npc.png" , "graphics/Npc/Priest_left.png" , "graphics/Npc/Priest_right.png" };

	//Npcによって動作を変える
	enum class NpcMove {
		Empty,				//空
		Herdman,			//村長
		Priest				//神官
	};

	//誰が動作を行うか
	NpcMove npcMove = NpcMove::Empty;

public:

	//inventory
	Shared<Inventory> GetInventory() { return inventory_; }

};