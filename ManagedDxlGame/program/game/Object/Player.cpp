#include "Player.h"
#include"../Manager/Camera.h"


Player::Player() : money(50)
{
	name = "Player";
	
	//csv�̓ǂݎ��
	PlyerStatus_Csv_Info
		= tnl::LoadCsv<tnl::CsvCell>("csv/PlyerStatus.csv");

	//�A�j���[�V�����̃��[�h����
	std::string files[DIR_MAX] = {
		"graphics/Player/pipo-charachip_Idle.png",
		"graphics/Player/pipo-charachip_UP.png",
		"graphics/Player/pipo-charachip_Left.png",
		"graphics/Player/pipo-charachip_Right.png"
		
	};

	for (int i = 0; i < 4; i++) {
		LoadDivGraph(
			files[i].c_str(),				// �摜�̃p�X
			Total_Frame,					// ���t���[����
			Horizontal_frame,				// ���t���[����
			Vertical_frame,					// �c�t���[����
			Horizontal_oneframe,			// �������� 1�t���[��������̕�
			Vertical_oneframe,				// �c������ 1�t���[��������̕�
			anim_hdls[i]);					// �摜�n���h�����i�[����z��);
	}

	//plyer�̃X�e�[�^�X���擾����
	PlyStatusLoad();

	//�v���C���[�̃X�e�[�^�X
	PlyerStatus plystatus = GetPlyerStatus(PlyerId);

	plyerstatusSave.emplace_back(plystatus);

}

void Player::Update(float delta_time)
{

}

void Player::player_Move(float delta_time , const float& velocity)
{
	prev_pos = plyer_pos;

	//�A�j���[�V����
	anim_time_count += delta_time;
	if (anim_time_count > 0.1f) {
		anim_ctrl_frame++;
		anim_ctrl_frame %= 3;

		anim_time_count = 0;
	}

	if (plyControl) {

		//�v���C���[�̓���
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


		//�A�j���[�V�����̓���
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

		//csv����id�̎擾
		plyerstatus_info.id = PlyerStatus_Csv_Info[y][0].getInt();
		//csv����hp�̎擾
		plyerstatus_info.hp = PlyerStatus_Csv_Info[y][1].getInt();
		//csv����Attack�̎擾
		plyerstatus_info.Attack = PlyerStatus_Csv_Info[y][2].getInt();
		//csv����Defance�̎擾
		plyerstatus_info.Defance = PlyerStatus_Csv_Info[y][3].getInt();
		//csv����Speed�̎擾
		plyerstatus_info.Speed = PlyerStatus_Csv_Info[y][4].getInt();
		//csv����K�v�Ȍo���l���������̎擾
		plyerstatus_info.R_expoint = PlyerStatus_Csv_Info[y][5].getInt();
		//csv����level���擾
		plyerstatus_info.level = PlyerStatus_Csv_Info[y][6].getInt();

		Ply_Status_Type.emplace_back(plyerstatus_info);

	}	

}

//�v���C���[�̍ő�HP���擾����
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


