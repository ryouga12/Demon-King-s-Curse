#include "mapScene.h"
#include"../Manager/SceneManager.h"
#include"resultScene.h"
#include"../Object/Player.h"


MapScene::MapScene(tnl::Vector3 PlyerPos , Shared<Inventory>inventory) :inventory_(inventory)
{
	camera = std::make_shared<Camera_>();
	myPlayer = std::make_shared<Player>();
	mapchip = std::make_shared<MapChip>();
	gmanager = std::make_shared<GameManager>();
	villageScene = std::make_shared<VillageScene>();
	SetInventory(inventory_);
	

	//Playerの初期位置を決める
	myPlayer->plyer_pos = myPlayer->SetAndGetPlayerPosition(PlyerPos);



	worldMapLoad();

}

void MapScene::Update(float delta_time)
{
	sequence_.update(delta_time);

	camera->update(myPlayer->plyer_pos , MAP_WIDTH , MAP_HEIGHT);

	myPlayer->player_Move(delta_time , 5);

	//Inventory
	UpdateCommon(delta_time);

	

	WorldMapCollision();

}

void MapScene::Draw()
{
	//MapChipの描画
	for (auto world_map : MapChip_continent) {
		world_map->Draw(*camera);
	}

	for (auto world_object : MapChips_object) {
		world_object->Draw(*camera);
	}

	myPlayer->player_draw(*camera , 1.0f);

	DrawStringEx(10, 10, -1, "マップ画面");
	DrawStringEx(100, 100, 0, "PlyerPos_X %f" , myPlayer->plyer_pos.x);
	DrawStringEx(100, 150, 0, "PlyerPos_Y %f" , myPlayer->plyer_pos.y);
	/*for (auto weapon : weapons) {
		DrawStringEx(100, 200, 0, "weaponName %s", weapon.name.c_str());
		DrawStringEx(100, 250, 0, "weaponAttack %d", weapon.damage);
	}*/

	DrawCommon();

}

bool MapScene::seqIdle(float delta_time)
{
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_1)) {
		auto mgr = SceneManager::GetInstance();
		mgr->changeScene(new ResultScene());
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		myPlayer->plyControl = false;
		inventory_->select_menu = Inventory::MenuWindow_I::First_Menu;
		inventory_->MenuChanege();
	}
	if (inventory_->select_menu == Inventory::MenuWindow_I::Empty) {
		myPlayer->plyControl = true;
	}

	return true;
}



void MapScene::WorldMapCollision()
{
	for (auto MapChip : MapChips_object) {
		int mapChipValue = world_object_csv[MapChip->pos_.y / MapChip->CHIP_SIZE][MapChip->pos_.x / MapChip->CHIP_SIZE];
		if (colisionObjectValues.count(mapChipValue) > 0)
		{
			int collision = gmanager->IsIntersectRectToCorrectPosition(myPlayer->plyer_pos, myPlayer->prev_pos, myPlayer->CHARA_WIDTH, myPlayer->CHARA_HEIGHT, MapChip->pos_, map_chip_width_, map_chip_height_);

		}
		if (villageValues.count(mapChipValue) > 0) {
			int villageCollision = tnl::IsIntersectRect(myPlayer->plyer_pos, myPlayer->CHARA_WIDTH, myPlayer->CHARA_HEIGHT, MapChip->pos_, map_chip_width_, map_chip_height_);
			if (villageCollision) {
				if (mapChipValue == 2035) {
					if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
						sequence_.change(&MapScene::seqChangeScene);
						auto mgr = SceneManager::GetInstance();
						mgr->changeScene(new VillageScene());
					}
				}
			}
		}



	}

	for (auto worldMap_C : MapChip_continent) {
		int mapChipValue = world_map_csv[worldMap_C->pos_.y / worldMap_C->CHIP_SIZE][worldMap_C->pos_.x / worldMap_C->CHIP_SIZE];
		if (worldCollisionValues.count(mapChipValue)) {
			int collison = gmanager->IsIntersectRectToCorrectPosition(myPlayer->plyer_pos, myPlayer->prev_pos, myPlayer->CHARA_WIDTH, myPlayer->CHARA_HEIGHT, worldMap_C->pos_, map_chip_width_, map_chip_height_);
		}
	}



}

void MapScene::worldMapLoad()
{
	// マップチップの画像のロード
	map_chip_ghdl_pass = "graphics/image_(2024_0115_0231).png";

	map_chip_width_ = 32;
	map_chip_height_ = 32;
	map_chip_x_size_ = 8;
	map_chip_y_size_ = 262;
	map_chip_all_size_ = map_chip_x_size_ * map_chip_y_size_;
	gpc_map_chip_hdls_ = new int[map_chip_all_size_];

	LoadDivGraph(map_chip_ghdl_pass.c_str(),
		map_chip_all_size_,
		map_chip_x_size_,
		map_chip_y_size_,
		map_chip_width_,
		map_chip_height_,
		gpc_map_chip_hdls_);

	//平原マップデータのロード
	map_chip_csv_pass = "csv/world_map_plain.csv";
	world_map_csv = tnl::LoadCsv<int>(map_chip_csv_pass);

	//オブジェクトデータのロード
	map_chip_csv_object_pass = "csv/world_map_object.csv";
	world_object_csv = tnl::LoadCsv<int>(map_chip_csv_object_pass);

	//平原のマップチップの読み込み
	for (int i = 0; i < world_map_csv.size(); ++i) {
		for (int k = 0; k < world_map_csv[i].size(); ++k) {
			if (-1 == world_map_csv[i][k])continue;
			tnl::Vector3 pos;
			int gpc_hdl;
			pos.x = { MapChip::CHIP_SIZE / 2 + k * MapChip::CHIP_SIZE };
			pos.y = { i * MapChip::CHIP_SIZE };
			gpc_hdl = gpc_map_chip_hdls_[world_map_csv[i][k]];
			MapChip_continent.emplace_back(new MapChip(pos, gpc_hdl));
		}
	}

	//オブジェクトのマップチップの読み込み
	for (int i = 0; i < world_object_csv.size(); ++i) {
		for (int k = 0; k <  world_object_csv[i].size(); ++k) {
			if (-1 == world_object_csv[i][k])continue;
			tnl::Vector3 pos;
			int gpc_hdl;
			pos.x = { MapChip::CHIP_SIZE / 2 + k * MapChip::CHIP_SIZE };
			pos.y = { i * MapChip::CHIP_SIZE };
			gpc_hdl = gpc_map_chip_hdls_[world_object_csv[i][k]];
			MapChips_object.emplace_back(new MapChip(pos, gpc_hdl));
		}
	}




}