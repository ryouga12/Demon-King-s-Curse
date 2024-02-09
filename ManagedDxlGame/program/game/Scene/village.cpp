#include "village.h"
#include"../Manager/SceneManager.h"
#include"battleScene.h"
#include "../dxlib_ext/dxlib_ext.h"
#include"mapScene.h"
#include<iostream>


//�R���X�g���N�^
VillageScene::VillageScene()
{
	InitVillageScene();

	mapChip_Loding();

	
}

VillageScene::~VillageScene()
{
}

//�X�V����
void VillageScene::Update(float delta_time)
{
	//�V�[�P���X
	sequence_.update(delta_time);
	//camera
	camera->update(my_player->plyer_pos , MAP_WIDTH , MAP_HEIGHT);

	//Player
	my_player->player_Move(delta_time , 5);

	//npc
	herdman_npc->Update(delta_time);
	Armsdealer_npc->Update(delta_time);
	Priest_npc->Update(delta_time);

	//���퉮
	weapon_shop->Update(delta_time);

	//Inventory
	UpdateCommon(delta_time);
		

	//�J�[�\���ő���ł���΍s��
	/*if (select_num == Sequence_num::WeaponShop) {
		CursourPosY = use_equip->GetCurrentCoursorY();
		id = use_equip->GetId();
	}*/

	mapChip_collision();

}

//�`��
void VillageScene::Draw()
{
	DrawStringEx(10, 10, -1, "�����");


	//---mapChip�̕`��---//
	for (auto mapchip : MapChips) {
		mapchip->Draw(*camera);
	}
	/*DrawStringEx(100, 500, -1, " id : %d", id);*/

	//---plyer�̕`��---//
	my_player->player_draw(*camera, 1.5f);
	DrawStringEx(100, 100, -1, "PlayerPos_x % f", my_player->plyer_pos.x);
	DrawStringEx(100, 150, -1, "PlayerPos_y % f", my_player->plyer_pos.y);

	//---Npc�̕`��---//
	herdman_npc->Draw(*camera);
	Armsdealer_npc->Draw(*camera);
	Priest_npc->Draw(*camera);

	int x = 10; // X ���W
	int y = 500; // ������ Y ���W

	//---����̃C���x���g����`��---//
	for (const auto Weapon : inventory_->GetInventoryList()) {

		std::string weaponName = Weapon.name; // ����̖��O
		int damage = Weapon.damage; // ����̈З�
		int Defance = Weapon.defance;//�h���

		//������� DrawString �ŕ\��
		DrawString(x, y, weaponName.c_str(), -1);
		DrawFormatString(x, y + 20, -1, "�З�: %d, ", damage);
		DrawStringEx(x, y + 40, -1, "�h���: %d, ", Defance);

		//���̗v�f��\�����邽�߂� Y ���W�𒲐�
		y += 60; // ��F40�s�N�Z�����ɕ\��

	}

	//---���ꂼ��̃V�[�P���X�ł̕`��---//
	
	//�ʏ��Ԃ̃V�[�P���X�̎�
	if (select_num == Sequence_num::Idle) {
		DrawStringEx(menuWindow->menu_x + 50, menuWindow->menu_y + 350, -1, "seqIdle");
	}

	//���퉮�̃V�[�P���X�̎�
	if (select_num == Sequence_num::WeaponShop) {
		menuComentWindiow->Menu_draw();

		//�R�����g�ƃA�C�R��
		DrawRotaGraph(90, 600, 1.5f, 0, Armsdealer_icon_hdl, true);
		DrawStringEx(menuComentWindiow->menu_x + 100, menuComentWindiow->menu_y + 50, -1, "�u ���𔃂��񂾂� �v");
		weapon_shop->Draw();
		DrawStringEx(135, 100, -1, "������: %d", my_player->money);

		/*use_equip->All();*/
		DrawStringEx(menuWindow->menu_x + 350, menuWindow->menu_y + 350, -1, "seqWeaponShop");

	}
	//---���j���[---//
	if (select_num == Sequence_num::MenuShopOpen)
	{
		if (select_menu_num == MenuOpenNum::WeaponShop) {
			menuSelectWindow->Menu_draw();
			menuComentWindiow->Menu_draw();
			/*menu_Back_Window->Menu_draw();*/

			DrawRotaGraph(90,600,1.5f ,0, Armsdealer_icon_hdl, true);
			DrawString(60, 520, "���퉮" , -1);
			DrawStringEx(menuComentWindiow->menu_x + 100, menuComentWindiow->menu_y+ 50, -1, "�u ��������Ⴂ�I�v");
			DrawStringEx(menuSelectWindow->menu_x + 20, menuSelectWindow->menu_y + 50, -1, "(1 : ������w������)");
			DrawStringEx(menuSelectWindow->menu_x + 20, menuSelectWindow->menu_y + 100, -1, "(0 : ���j���[�����)");
			DrawStringEx(menuSelectWindow->menu_x + 50, menuSelectWindow->menu_y + 250, -1, "seqMenuOpen");
		}
	}
	//Npc�̃��j���[
	if (select_num == Sequence_num::MenuOpen) {
		if (select_menu_num == MenuOpenNum::Herdman || select_menu_num == MenuOpenNum::Priest) {
			menuSelectWindow->Menu_draw();
			DrawStringEx(80, 100, -1, "(1 : �b��)");
			DrawStringEx(80, 150, -1, "(0 : ���j���[�����)");
		}
		if (select_menu_num == MenuOpenNum::Object) {
			menuComentWindiow->Menu_draw();
			DrawRotaGraph(menuComentWindiow->menu_x + 50, menuComentWindiow->menu_y + 90, 1.5f, 0, Player_icon_hdl, true);
			DrawStringEx(menuComentWindiow->menu_x + 100, menuComentWindiow->menu_y + 50, -1, "�u ���͎g���Ă��Ȃ��B�݂�����\n   �K�тĂ���                 �v");
			DrawStringEx(menuComentWindiow->menu_x + 100, menuComentWindiow->menu_y+ 150,-1, "(0 : ���j���[�����)");
		}
	}
	//Npc�ɂ���ĕ\����ς���
	if (select_num == Sequence_num::MenuNpc) {
		//�����̎�
		if (npcMove == NpcMove::Herdman) {
			menuComentWindiow->Menu_draw();
			DrawRotaGraph(menuComentWindiow->menu_x + 60, menuComentWindiow->menu_y + 100, 1.5f, 0, herdman_icon_hdl, true);
			DrawStringEx(menuComentWindiow->menu_x + 100, menuComentWindiow->menu_y + 70 , -1, "�u ���͂悤 �v");
		}
	}
	if (select_num == Sequence_num::MenuNpc) {
		//�_���̎�
		if (npcMove == NpcMove::Priest) {
			menuComentWindiow->Menu_draw();
			menuSelectWindow->Menu_draw();
			DrawRotaGraph(menuComentWindiow->menu_x + 60, menuComentWindiow->menu_y + 100, 1.5f, 0, Priest_icon_hdl, true);
			DrawStringEx(menuComentWindiow->menu_x + 100 , menuComentWindiow->menu_y + 70, -1, "�u �悭������ �v");
		}
	}

	/*inventory_->draw();*/
	DrawCommon();
	
	/*DrawStringEx(100, 500, 0, "%d", inventoryDraw.size());*/
	
} 


//������
void VillageScene::InitVillageScene()
{
	//�J�����̏�����
	camera = std::make_shared<Camera_>();

	//�v���C���[�̏�����
	my_player = std::make_shared<Player>();

	//Player�̏����ʒu�����߂�
	my_player->plyer_pos = my_player->SetAndGetPlayerPosition(first_pos);


	//GamaManager�̏�����
	gmanager = new GameManager();


	//����֘A�̏�����
	weapon = std::make_shared<Weapon>();
	weapon_shop = std::make_shared<WeaponShop>();

	//�C���x���g���̏�����
	inventory_ = std::make_shared<Inventory>();
	weapon_shop->setInventory(inventory_);
	SetInventory(inventory_);
	



	//�V�X�e���}�l�[�W���[�̏�����
	systemManager = std::make_shared<SystemManager>();

	//NPC�̏�����
	herdman_npc = std::make_shared<Npc>("����", tnl::Vector3(1375, 760, 0), herdman_hdl_pass, 1.5f , 0 , 4);
	Armsdealer_npc = std::make_shared<Npc>("���폤�l", tnl::Vector3(1150, 140 , 0), Armsdealer_hdl_pass, 1.5f, 0 , 1);
	Priest_npc = std::make_shared<Npc>("�_��", tnl::Vector3(239, 740, 0), Priest_hdl_pass, 1.5f, 0 , 3);

	//���j���[�Ŏg���A�C�R��
	Armsdealer_icon_hdl = gmanager->LoadGraphEX("graphics/Npc/Armsdealer_icon.png");
	herdman_icon_hdl = gmanager->LoadGraphEX("graphics/Npc/herdman_icon.png");
	Priest_icon_hdl = gmanager->LoadGraphEX("graphics/Npc/Priest_icon.png");
	Player_icon_hdl = gmanager->LoadGraphEX("graphics/Player/Player_Icon.png");

	//���j���[�̏�����
	menuWindow = std::make_shared<Menu>(50, 50, 300, 270, "graphics/WindowBase_01.png");
	menuSelectWindow = std::make_shared<Menu>(50, 50, 250, 200, "graphics/WindowBase_01.png");
	menuComentWindiow = std::make_shared<Menu>(50, 500, 700, 200, "graphics/WindowBase_01.png");

	

	/*menu_usable = new MenuWindow::MenuElement_t[]{
		{100, 100 , "��",0}
		{100, 150 , "��",1},
		{100, 200 , "��",2}

	};*/
	/*use_equip = new MenuWindow(50, 50, 250, 200, "graphics/WindowBase_01.png", menu_usable, 3, 1);*/


}

//�V�[���J��
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

//���퉮
bool VillageScene::seqWeaponShop(float delta_time)
{
	
	if (sequence_.isStart()) {
		select_num = Sequence_num::WeaponShop;
		weapon_shop->buyWeapon =  weapon_shop->buyComentClear();
		/*use_equip->Open();*/
	}

	//���퉮�̏���
	weapon_shop->BuyWeapon(my_player);
	


	//0����������V�[�P���X��ς���
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_0)) {
		my_player->plyControl = true;
		sequence_.change(&VillageScene::seqIdle);
	}


	return true;
}

//�V�[����ς��鎞�̃t�F�[�h�A�E�g�������
bool VillageScene::seqChangeScene(float delta_time)
{
	return true;
}

//���j���[
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
		//�ŏ��̑Ԑ��ƈ���Ă�����߂�
		if (herdman_npc->animation_select != 0) {
			herdman_npc->animation_select = 0;
			herdman_npc->ChengeAnimation();
		}
		my_player->plyControl = true;
	}

	return true;

}

//Npc�̏���
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


//����������
void VillageScene::mapChip_Loding()
{
	// �}�b�v�`�b�v�̉摜�̃��[�h
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

	// �}�b�v�f�[�^�̃��[�h
	map_data_csv_pass_ = "csv/map_chip_first_village.csv";
	map_csv = tnl::LoadCsv<int>(map_data_csv_pass_);

	//�}�b�v�`�b�v�ǂݍ���
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

//�����蔻��̏���
void VillageScene::mapChip_collision()
{
	 //�u���b�N�ƏՓ˔��� & �␳
	 //�Q�[�����[�v���ł̓����蔻��̃`�F�b�N]
	for (auto mapChip : MapChips) {
		int mapChipValue = map_csv[mapChip->pos_.y / mapChip->CHIP_SIZE][mapChip->pos_.x / mapChip->CHIP_SIZE];
		if(colisionValues.count(mapChipValue) > 0)
		{
			int collision = gmanager->IsIntersectRectToCorrectPosition(my_player->plyer_pos, my_player->prev_pos, my_player->CHARA_WIDTH, my_player->CHARA_HEIGHT, mapChip->pos_, map_chip_width_, map_chip_height_);
			//�����蔻�肪��p�����ۂɂ��̔ԍ���510�Ԃ������ꍇ�Awindow��\������
			if (collision) {
				//���퉮�Ƙb�����ꍇ
				
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

					//�����Ƙb������
					if (mapChipValue == 708) {
						if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
							select_num = Sequence_num::MenuOpen;
							select_menu_num = MenuOpenNum::Herdman;
							sequence_.change(&VillageScene::seqMenuOpen);
						}
					}
					//�I�u�W�F�N�g�ɐG�ꂽ�Ƃ�
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

	//---Npc�̓����蔻��---//

	//����
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

		//�����瓖��������
		bool playerOnBottom = my_player->plyer_pos.y >= herdman_npc->npc_pos_.y + herdman_npc->NpcCharaChipHeight;

		if (playerOnBottom) {
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				//�A�j���[�V���������ɂ���
				herdman_npc->animation_select = 1;
				herdman_npc->ChengeAnimation();
				select_num = Sequence_num::MenuOpen;
				select_menu_num = MenuOpenNum::Herdman;
				sequence_.change(&VillageScene::seqMenuOpen);
			}
		}
	}

	//�_��
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
		//�����瓖��������
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
