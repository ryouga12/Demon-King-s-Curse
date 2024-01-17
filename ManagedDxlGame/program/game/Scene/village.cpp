#include "village.h"
#include"../Manager/SceneManager.h"
#include"battleScene.h"
#include "../dxlib_ext/dxlib_ext.h"


//コンストラクタ
VillageScene::VillageScene()
{
	camera = std::make_shared<Camera_>();
	my_player = std::make_shared<Player>(10 , 5, 3);
	mapChip_Loding();
}

//更新処理
void VillageScene::Update(float delta_time)
{
	sequence_.update(delta_time);
	camera->update(my_player->plyer_pos);
	my_player->player_Move(delta_time);
}

//描画
void VillageScene::Draw()
{
	DrawStringEx(10, 10, -1, "村画面");
	for (auto mapchip : MapChips) {
		mapchip->Draw(*camera);
	}
	my_player->player_draw(*camera);
	
}

//シーン遷移
bool VillageScene::seqIdle(float delta_time)
{
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		auto mgr = SceneManager::GetInstance();
		mgr->changeScene(new BattleScene());
	}
	return true;
}

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

//void VillageScene::mapChip_collision()
//{
//	// ブロックと衝突判定 & 補正
//	// ゲームループ内での当たり判定のチェック]
//	for (auto mapChip : MapChips) {
//		int mapChipValue = map_csv[mapChip->pos_.y / mapChip->CHIP_SIZE][mapChip->pos_.x / mapChip->CHIP_SIZE];
//		if (mapChipValue == -1 ||
//			mapChipValue == 324 ||
//			mapChipValue == 384 ||
//			mapChipValue == 392 ||
//			mapChipValue == 545 ||
//			mapChipValue == 528 ||
//			mapChipValue == 536 ||
//			mapChipValue == 464 ||
//			mapChipValue == 631 ||
//			mapChipValue == 708 ||
//			mapChipValue == 614 ||
//			mapChipValue == 630 ||
//			mapChipValue == 510 ||
//			mapChipValue == 400 ||
//			mapChipValue == 408 ||
//			mapChipValue == 657 ||
//			mapChipValue == 656 ||
//			mapChipValue == 395 ||
//			mapChipValue == 230 ||
//			mapChipValue == 231
//			) {
//			int n = tnl::IsIntersectRectToCorrectPosition(
//				myplayer->plyer_pos,
//				myplayer->prev_pos,
//				myplayer->CHARA_WIDTH,
//				myplayer->CHARA_HEIGHT,
//				mapChip->pos_,
//				map_chip_width_,
//				map_chip_height_);
//		}
//
//	}
//}
