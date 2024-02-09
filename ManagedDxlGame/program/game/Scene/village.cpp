#include "village.h"
#include"../Manager/SceneManager.h"
#include"battleScene.h"
#include "../dxlib_ext/dxlib_ext.h"
#include"mapScene.h"
#include<iostream>


//コンストラクタ
VillageScene::VillageScene()
{
	InitVillageScene();

	mapChip_Loding();

	
}

VillageScene::~VillageScene()
{
}

//更新処理
void VillageScene::Update(float delta_time)
{
	//シーケンス
	sequence_.update(delta_time);
	//camera
	camera->update(my_player->plyer_pos , MAP_WIDTH , MAP_HEIGHT);

	//Player
	my_player->player_Move(delta_time , 5);

	//npc
	herdman_npc->Update(delta_time);
	Armsdealer_npc->Update(delta_time);
	Priest_npc->Update(delta_time);

	//武器屋
	weapon_shop->Update(delta_time);

	//Inventory
	UpdateCommon(delta_time);
		

	//カーソルで操作できれば行う
	/*if (select_num == Sequence_num::WeaponShop) {
		CursourPosY = use_equip->GetCurrentCoursorY();
		id = use_equip->GetId();
	}*/

	mapChip_collision();

}

//描画
void VillageScene::Draw()
{
	DrawStringEx(10, 10, -1, "村画面");


	//---mapChipの描画---//
	for (auto mapchip : MapChips) {
		mapchip->Draw(*camera);
	}
	/*DrawStringEx(100, 500, -1, " id : %d", id);*/

	//---plyerの描画---//
	my_player->player_draw(*camera, 1.5f);
	DrawStringEx(100, 100, -1, "PlayerPos_x % f", my_player->plyer_pos.x);
	DrawStringEx(100, 150, -1, "PlayerPos_y % f", my_player->plyer_pos.y);

	//---Npcの描画---//
	herdman_npc->Draw(*camera);
	Armsdealer_npc->Draw(*camera);
	Priest_npc->Draw(*camera);

	int x = 10; // X 座標
	int y = 500; // 初期の Y 座標

	//---武器のインベントリを描画---//
	for (const auto Weapon : inventory_->GetInventoryList()) {

		std::string weaponName = Weapon.name; // 武器の名前
		int damage = Weapon.damage; // 武器の威力
		int Defance = Weapon.defance;//防御力

		//武器情報を DrawString で表示
		DrawString(x, y, weaponName.c_str(), -1);
		DrawFormatString(x, y + 20, -1, "威力: %d, ", damage);
		DrawStringEx(x, y + 40, -1, "防御力: %d, ", Defance);

		//次の要素を表示するために Y 座標を調整
		y += 60; // 例：40ピクセル下に表示

	}

	//---それぞれのシーケンスでの描画---//
	
	//通常状態のシーケンスの時
	if (select_num == Sequence_num::Idle) {
		DrawStringEx(menuWindow->menu_x + 50, menuWindow->menu_y + 350, -1, "seqIdle");
	}

	//武器屋のシーケンスの時
	if (select_num == Sequence_num::WeaponShop) {
		menuComentWindiow->Menu_draw();

		//コメントとアイコン
		DrawRotaGraph(90, 600, 1.5f, 0, Armsdealer_icon_hdl, true);
		DrawStringEx(menuComentWindiow->menu_x + 100, menuComentWindiow->menu_y + 50, -1, "「 何を買うんだい 」");
		weapon_shop->Draw();
		DrawStringEx(135, 100, -1, "所持金: %d", my_player->money);

		/*use_equip->All();*/
		DrawStringEx(menuWindow->menu_x + 350, menuWindow->menu_y + 350, -1, "seqWeaponShop");

	}
	//---メニュー---//
	if (select_num == Sequence_num::MenuShopOpen)
	{
		if (select_menu_num == MenuOpenNum::WeaponShop) {
			menuSelectWindow->Menu_draw();
			menuComentWindiow->Menu_draw();
			/*menu_Back_Window->Menu_draw();*/

			DrawRotaGraph(90,600,1.5f ,0, Armsdealer_icon_hdl, true);
			DrawString(60, 520, "武器屋" , -1);
			DrawStringEx(menuComentWindiow->menu_x + 100, menuComentWindiow->menu_y+ 50, -1, "「 いらっしゃい！」");
			DrawStringEx(menuSelectWindow->menu_x + 20, menuSelectWindow->menu_y + 50, -1, "(1 : 武器を購入する)");
			DrawStringEx(menuSelectWindow->menu_x + 20, menuSelectWindow->menu_y + 100, -1, "(0 : メニューを閉じる)");
			DrawStringEx(menuSelectWindow->menu_x + 50, menuSelectWindow->menu_y + 250, -1, "seqMenuOpen");
		}
	}
	//Npcのメニュー
	if (select_num == Sequence_num::MenuOpen) {
		if (select_menu_num == MenuOpenNum::Herdman || select_menu_num == MenuOpenNum::Priest) {
			menuSelectWindow->Menu_draw();
			DrawStringEx(80, 100, -1, "(1 : 話す)");
			DrawStringEx(80, 150, -1, "(0 : メニューを閉じる)");
		}
		if (select_menu_num == MenuOpenNum::Object) {
			menuComentWindiow->Menu_draw();
			DrawRotaGraph(menuComentWindiow->menu_x + 50, menuComentWindiow->menu_y + 90, 1.5f, 0, Player_icon_hdl, true);
			DrawStringEx(menuComentWindiow->menu_x + 100, menuComentWindiow->menu_y + 50, -1, "「 今は使われていない檻みたいだ\n   錆びている                 」");
			DrawStringEx(menuComentWindiow->menu_x + 100, menuComentWindiow->menu_y+ 150,-1, "(0 : メニューを閉じる)");
		}
	}
	//Npcによって表示を変える
	if (select_num == Sequence_num::MenuNpc) {
		//村長の時
		if (npcMove == NpcMove::Herdman) {
			menuComentWindiow->Menu_draw();
			DrawRotaGraph(menuComentWindiow->menu_x + 60, menuComentWindiow->menu_y + 100, 1.5f, 0, herdman_icon_hdl, true);
			DrawStringEx(menuComentWindiow->menu_x + 100, menuComentWindiow->menu_y + 70 , -1, "「 おはよう 」");
		}
	}
	if (select_num == Sequence_num::MenuNpc) {
		//神官の時
		if (npcMove == NpcMove::Priest) {
			menuComentWindiow->Menu_draw();
			menuSelectWindow->Menu_draw();
			DrawRotaGraph(menuComentWindiow->menu_x + 60, menuComentWindiow->menu_y + 100, 1.5f, 0, Priest_icon_hdl, true);
			DrawStringEx(menuComentWindiow->menu_x + 100 , menuComentWindiow->menu_y + 70, -1, "「 よく来たな 」");
		}
	}

	/*inventory_->draw();*/
	DrawCommon();
	
	/*DrawStringEx(100, 500, 0, "%d", inventoryDraw.size());*/
	
} 


//初期化
void VillageScene::InitVillageScene()
{
	//カメラの初期化
	camera = std::make_shared<Camera_>();

	//プレイヤーの初期化
	my_player = std::make_shared<Player>();

	//Playerの初期位置を決める
	my_player->plyer_pos = my_player->SetAndGetPlayerPosition(first_pos);


	//GamaManagerの初期化
	gmanager = new GameManager();


	//武器関連の初期化
	weapon = std::make_shared<Weapon>();
	weapon_shop = std::make_shared<WeaponShop>();

	//インベントリの初期化
	inventory_ = std::make_shared<Inventory>();
	weapon_shop->setInventory(inventory_);
	SetInventory(inventory_);
	



	//システムマネージャーの初期化
	systemManager = std::make_shared<SystemManager>();

	//NPCの初期化
	herdman_npc = std::make_shared<Npc>("村長", tnl::Vector3(1375, 760, 0), herdman_hdl_pass, 1.5f , 0 , 4);
	Armsdealer_npc = std::make_shared<Npc>("武器商人", tnl::Vector3(1150, 140 , 0), Armsdealer_hdl_pass, 1.5f, 0 , 1);
	Priest_npc = std::make_shared<Npc>("神官", tnl::Vector3(239, 740, 0), Priest_hdl_pass, 1.5f, 0 , 3);

	//メニューで使うアイコン
	Armsdealer_icon_hdl = gmanager->LoadGraphEX("graphics/Npc/Armsdealer_icon.png");
	herdman_icon_hdl = gmanager->LoadGraphEX("graphics/Npc/herdman_icon.png");
	Priest_icon_hdl = gmanager->LoadGraphEX("graphics/Npc/Priest_icon.png");
	Player_icon_hdl = gmanager->LoadGraphEX("graphics/Player/Player_Icon.png");

	//メニューの初期化
	menuWindow = std::make_shared<Menu>(50, 50, 300, 270, "graphics/WindowBase_01.png");
	menuSelectWindow = std::make_shared<Menu>(50, 50, 250, 200, "graphics/WindowBase_01.png");
	menuComentWindiow = std::make_shared<Menu>(50, 500, 700, 200, "graphics/WindowBase_01.png");

	

	/*menu_usable = new MenuWindow::MenuElement_t[]{
		{100, 100 , "剣",0}
		{100, 150 , "剣",1},
		{100, 200 , "剣",2}

	};*/
	/*use_equip = new MenuWindow(50, 50, 250, 200, "graphics/WindowBase_01.png", menu_usable, 3, 1);*/


}

//シーン遷移
bool VillageScene::seqIdle(float delta_time)
{
	if (sequence_.isStart()) {
		select_num = Sequence_num::Idle;
		drawSeqFlag = true;
		
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		my_player->plyControl = false;
		inventory_->select_menu = Inventory::MenuWindow_I::First_Menu;
		inventory_->MenuChanege();
	}
	if (inventory_->select_menu == Inventory::MenuWindow_I::Empty) {
		my_player->plyControl = true;
	}

	


	if (my_player->plyer_pos.x >= MAP_WIDTH ||my_player->plyer_pos.x < 0|| my_player->plyer_pos.y >= MAP_HEIGHT /*tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)*/)
	{
		sequence_.change(&VillageScene::seqChangeScene);
		auto mgr = SceneManager::GetInstance();
		mgr->changeScene(new MapScene(first_world_pos , inventory_));

	}


	return true;
}

//武器屋
bool VillageScene::seqWeaponShop(float delta_time)
{
	
	if (sequence_.isStart()) {
		select_num = Sequence_num::WeaponShop;
		weapon_shop->buyWeapon =  weapon_shop->buyComentClear();
		/*use_equip->Open();*/
	}

	//武器屋の処理
	weapon_shop->BuyWeapon(my_player);
	


	//0を押したらシーケンスを変える
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_0)) {
		my_player->plyControl = true;
		sequence_.change(&VillageScene::seqIdle);
	}


	return true;
}

//シーンを変える時のフェードアウトを入れる為
bool VillageScene::seqChangeScene(float delta_time)
{
	return true;
}

//メニュー
bool VillageScene::seqMenuOpen(float delta_time)
{
	if (sequence_.isStart())
	{
		/*select_num = Sequence_num::MenuShopOpen;*/
		my_player->plyControl = false;
	}

	if (select_menu_num == MenuOpenNum::Herdman) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_1)) {
			sequence_.change(&VillageScene::seqNpc);
			npcMove = NpcMove::Herdman;
		}
	}
	else if (select_menu_num == MenuOpenNum::Priest) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_1)) {
			sequence_.change(&VillageScene::seqNpc);
			npcMove = NpcMove::Priest;
		}
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_0)) {
		sequence_.change(&VillageScene::seqIdle);
		//最初の態勢と違っていたら戻す
		if (herdman_npc->animation_select != 0) {
			herdman_npc->animation_select = 0;
			herdman_npc->ChengeAnimation();
		}
		my_player->plyControl = true;
	}

	return true;

}

//Npcの処理
bool VillageScene::seqNpc(float delta_time)
{
	if (sequence_.isStart()) {
		select_num = Sequence_num::MenuNpc;
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_0)) {
		sequence_.change(&VillageScene::seqIdle);
		my_player->plyControl = true;
		
	}

	return true;
}


//初期化処理
void VillageScene::mapChip_Loding()
{
	// マップチップの画像のロード
	gpc_map_chip_hdls_pass_ = "graphics/BaseChip_pipo.png";


	map_chip_width_ = 32;
	map_chip_height_ = 32;
	map_chip_x_size_ = 8;
	map_chip_y_size_ = 249;
	map_chip_all_size_ = map_chip_x_size_ * map_chip_y_size_;
	gpc_map_chip_hdls_ = new int[map_chip_all_size_];

	LoadDivGraph(gpc_map_chip_hdls_pass_.c_str(),
		map_chip_all_size_,
		map_chip_x_size_,
		map_chip_y_size_,
		map_chip_width_,
		map_chip_height_,
		gpc_map_chip_hdls_);

	// マップデータのロード
	map_data_csv_pass_ = "csv/map_chip_first_village.csv";
	map_csv = tnl::LoadCsv<int>(map_data_csv_pass_);

	//マップチップ読み込み
	for (int i = 0; i < map_csv.size(); ++i) {
		for (int k = 0; k < map_csv[i].size(); ++k) {
			if (-1 == map_csv[i][k]) continue;
			tnl::Vector3 pos;
			int gpc_hdl;
			pos.x = { MapChip::CHIP_SIZE / 2 + k * MapChip::CHIP_SIZE };
			pos.y = { i * MapChip::CHIP_SIZE };
			gpc_hdl = gpc_map_chip_hdls_[map_csv[i][k]];
			/*DrawGraph(pos.x, pos.y, gpc_hdl, true);*/
			MapChips.emplace_back(new MapChip(pos, gpc_hdl));

			
		}
	}
}

//あたり判定の処理
void VillageScene::mapChip_collision()
{
	 //ブロックと衝突判定 & 補正
	 //ゲームループ内での当たり判定のチェック]
	for (auto mapChip : MapChips) {
		int mapChipValue = map_csv[mapChip->pos_.y / mapChip->CHIP_SIZE][mapChip->pos_.x / mapChip->CHIP_SIZE];
		if(colisionValues.count(mapChipValue) > 0)
		{
			int collision = gmanager->IsIntersectRectToCorrectPosition(my_player->plyer_pos, my_player->prev_pos, my_player->CHARA_WIDTH, my_player->CHARA_HEIGHT, mapChip->pos_, map_chip_width_, map_chip_height_);
			//あたり判定が作用した際にその番号が510番だった場合、windowを表示する
			if (collision) {
				//武器屋と話した場合
				
					if (mapChipValue == 510) {
						if (select_num == Sequence_num::Idle) {
							if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
								select_menu_num = MenuOpenNum::WeaponShop;
								select_num = Sequence_num::MenuShopOpen;
								sequence_.change(&VillageScene::seqMenuOpen);
							}
						}
						if (tnl::Input::IsKeyDownTrigger(eKeys::KB_1)) {
							if (select_num == Sequence_num::MenuShopOpen) {
								sequence_.change(&VillageScene::seqWeaponShop);
							}
						}
					}

					//村長と話した時
					if (mapChipValue == 708) {
						if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
							select_num = Sequence_num::MenuOpen;
							select_menu_num = MenuOpenNum::Herdman;
							sequence_.change(&VillageScene::seqMenuOpen);
						}
					}
					//オブジェクトに触れたとき
					if (mapChipValue == 545) {
						if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
							select_num = Sequence_num::MenuOpen;
							select_menu_num = MenuOpenNum::Object;
							sequence_.change(&VillageScene::seqMenuOpen);
						}
					}
				
			
			}
		}
		
	}

	//---Npcの当たり判定---//

	//村長
	int h_colition = gmanager->IsIntersectRectToCorrectPosition(
					my_player->plyer_pos,
					my_player->prev_pos,
					my_player->CHARA_WIDTH,
					my_player->CHARA_HEIGHT,
					herdman_npc->npc_pos_,
					herdman_npc->NpcCharaChipWidth,
					herdman_npc->NpcCharaChipHeight
				);


	if (h_colition) {

		//下から当たった時
		bool playerOnBottom = my_player->plyer_pos.y >= herdman_npc->npc_pos_.y + herdman_npc->NpcCharaChipHeight;

		if (playerOnBottom) {
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				//アニメーションを下にする
				herdman_npc->animation_select = 1;
				herdman_npc->ChengeAnimation();
				select_num = Sequence_num::MenuOpen;
				select_menu_num = MenuOpenNum::Herdman;
				sequence_.change(&VillageScene::seqMenuOpen);
			}
		}
	}

	//神官
	int P_collision = gmanager->IsIntersectRectToCorrectPosition
	(
		my_player->plyer_pos,
		my_player->prev_pos,
		my_player->CHARA_WIDTH,
		my_player->CHARA_HEIGHT,
		Priest_npc->npc_pos_,
		Priest_npc->NpcCharaChipWidth,
		Priest_npc->NpcCharaChipHeight
	);


	if (P_collision) {
		//下から当たった時
		bool playerOnBottom = my_player->plyer_pos.y >= Priest_npc->npc_pos_.y + Priest_npc->NpcCharaChipHeight;
		
		if (playerOnBottom) {
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				Priest_npc->animation_select = 0;
				Priest_npc->ChengeAnimation();
				select_num = Sequence_num::MenuOpen;
				select_menu_num = MenuOpenNum::Priest;
				sequence_.change(&VillageScene::seqMenuOpen);
			}
		}
	}


}
