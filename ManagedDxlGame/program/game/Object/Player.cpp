#include "Player.h"
#include"../Manager/Camera.h"


Player::Player() : money(50)
{
	name = "Player";
	
	//csvの読み取り
	PlyerStatus_Csv_Info
		= tnl::LoadCsv<tnl::CsvCell>("csv/PlyerStatus.csv");

	//アニメーションのロード処理
	std::string files[DIR_MAX] = {
		"graphics/Player/pipo-charachip_Idle.png",
		"graphics/Player/pipo-charachip_UP.png",
		"graphics/Player/pipo-charachip_Left.png",
		"graphics/Player/pipo-charachip_Right.png"
		
	};

	for (int i = 0; i < 4; i++) {
		LoadDivGraph(
			files[i].c_str(),				// 画像のパス
			Total_Frame,					// 総フレーム数
			Horizontal_frame,				// 横フレーム数
			Vertical_frame,					// 縦フレーム数
			Horizontal_oneframe,			// 横方向へ 1フレームあたりの幅
			Vertical_oneframe,				// 縦方向へ 1フレームあたりの幅
			anim_hdls[i]);					// 画像ハンドルを格納する配列名);
	}

	//plyerのステータスを取得する
	PlyStatusLoad();

	//プレイヤーのステータス
	PlyerStatus plystatus = GetPlyerStatus(PlyerId);

	plyerstatusSave.emplace_back(plystatus);

}

void Player::Update(float delta_time)
{

}

void Player::player_Move(float delta_time , const float& velocity)
{
	prev_pos = plyer_pos;

	//アニメーション
	anim_time_count += delta_time;
	if (anim_time_count > 0.1f) {
		anim_ctrl_frame++;
		anim_ctrl_frame %= 3;

		anim_time_count = 0;
	}

	if (plyControl) {

		//プレイヤーの動き
		if (tnl::Input::IsKeyDown(eKeys::KB_A)) {
			plyer_pos.x -= velocity;
		}
		if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
			plyer_pos.x += velocity;
		}

		if (tnl::Input::IsKeyDown(eKeys::KB_W)) {
			plyer_pos.y -= velocity;
		}
		if (tnl::Input::IsKeyDown(eKeys::KB_S)) {
			plyer_pos.y += velocity;
		}


		//アニメーションの動き
		if (tnl::Input::IsKeyDown(eKeys::KB_W))    anim_ctrl_dir = DIR_UP;
		if (tnl::Input::IsKeyDown(eKeys::KB_S))    anim_ctrl_dir = DIR_DOWN;
		if (tnl::Input::IsKeyDown(eKeys::KB_A))	   anim_ctrl_dir = DIR_LEFT;
		if (tnl::Input::IsKeyDown(eKeys::KB_D))    anim_ctrl_dir = DIR_RIGHT;

	}
}

void Player::player_draw(const Camera_& camera ,float scale)
{
	tnl::Vector3 draw_pos = plyer_pos - camera.target_ + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
	DrawRotaGraph(draw_pos.x, draw_pos.y, scale, 0, anim_hdls[anim_ctrl_dir][anim_ctrl_frame], true);

}

void Player::PlyStatusLoad()
{
	int max_num = PlyerStatus_Csv_Info.size();

	Ply_Status_Total_num = max_num;

	for (int y = 1; y < max_num; y++) {
		PlyerStatus plyerstatus_info;

		//csvからidの取得
		plyerstatus_info.id = PlyerStatus_Csv_Info[y][0].getInt();
		//csvからhpの取得
		plyerstatus_info.hp = PlyerStatus_Csv_Info[y][1].getInt();
		//csvからAttackの取得
		plyerstatus_info.Attack = PlyerStatus_Csv_Info[y][2].getInt();
		//csvからDefanceの取得
		plyerstatus_info.Defance = PlyerStatus_Csv_Info[y][3].getInt();
		//csvからSpeedの取得
		plyerstatus_info.Speed = PlyerStatus_Csv_Info[y][4].getInt();
		//csvから必要な経験値がいくつかの取得
		plyerstatus_info.R_expoint = PlyerStatus_Csv_Info[y][5].getInt();
		//csvからlevelを取得
		plyerstatus_info.level = PlyerStatus_Csv_Info[y][6].getInt();

		Ply_Status_Type.emplace_back(plyerstatus_info);

	}	

}

//プレイヤーの最大HPを取得する
int Player::PlyerMaxHp(int id)
{
	MaxHp = GetPlyerStatus(id).hp;

	return MaxHp;
}

void Player::PlyerSave()
{
	FILE* fp = nullptr;
	fopen_s(&fp, "player.bin", "wb");

	for (const auto& Plyerstatus : plyerstatusSave) {

		
		if (fp) {
			fwrite(&Plyerstatus.hp, sizeof(int), 1, fp);
			fwrite(&Plyerstatus.Attack, sizeof(int), 1, fp);
			fwrite(&Plyerstatus.Defance, sizeof(int), 1, fp);
			fwrite(&Plyerstatus.Speed, sizeof(int), 1, fp);
			fwrite(&Plyerstatus.level, sizeof(int), 1, fp);
			fwrite(&Plyerstatus.R_expoint, sizeof(int), 1, fp);
			fwrite(&plyer_pos, sizeof(tnl::Vector3), 1, fp);

			fclose(fp);
		}

	}
}

void Player::PlyerLoad()
{
	FILE* fp = nullptr;
	fopen_s(&fp, "player.bin", "rb");
	
	for (auto Plyerstatus : plyerstatusSave) {

		if (fp) {
			fread(&Plyerstatus.hp, sizeof(int), 1, fp);
			fread(&Plyerstatus.Attack, sizeof(int), 1, fp);
			fread(&Plyerstatus.Defance, sizeof(int), 1, fp);
			fread(&Plyerstatus.Speed, sizeof(int), 1, fp);
			fread(&Plyerstatus.level, sizeof(int), 1, fp);
			fread(&Plyerstatus.R_expoint, sizeof(int), 1, fp);
			fread(&plyer_pos, sizeof(tnl::Vector3), 1, fp);

			fclose(fp);
		}

	}



}


