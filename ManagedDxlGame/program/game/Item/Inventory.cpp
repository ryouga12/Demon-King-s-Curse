#include "Inventory.h"



Inventory::Inventory()
{
	item = std::make_shared<Item>();
	plyer = std::make_shared<Player>();
	gm_Manager = std::make_shared<GameManager>();


	plyerstatus = plyer->GetPlyerStatus(PlyerStatus_Id);

	cursorGh = gm_Manager->LoadGraphEX("graphics/cur_sannkaku2.png");

	//�ŏ���ESC���������Ƃ��ɏo��ŏ��̃��j���[
	MenuWindow::MenuElement_t* first_menu_coment = new MenuWindow::MenuElement_t[]
	{
		{100, 100 , "����",0},
		{100, 150 , "����",1},
		{100, 200 , "����",2}
	};

	first_menu = std::make_shared<MenuWindow>(50, 50, 250, 200, "graphics/WindowBase_01.png", first_menu_coment, 3, 1);

	//�v���C���[�̑I�����Ă��炤���j���[
	MenuWindow::MenuElement_t* select_menu_coment = new MenuWindow::MenuElement_t[]
	{
		{ 100 , 100 , "�͂�" , 0},
		{ 100 , 150 , "������" , 1}
	};

	select_action_menu = std::make_shared<MenuWindow>(50, 50, 250, 200, "graphics/WindowBase_01.png", select_menu_coment, 2, 1);

	//�A�C�e���E�B���h�E���őI�����郁�j���[
	MenuWindow::MenuElement_t* select_detail = new MenuWindow::MenuElement_t[]
	{
		{400 , 100 , "�g��" , 0},
		{400 , 150 , "�ڍ�" , 1},
		{400 , 200 , "����" , 2}
	};

	select_detail_window = std::make_shared<MenuWindow>(350, 50, 250, 200, "graphics/WindowBase_01.png", select_detail, 3, 1);

	//���j���[�E�B���h�E
	menu_window = std::make_shared<Menu>(50, 50, 300, 270, "graphics/WindowBase_01.png");
	item_coment_window = std::make_shared<Menu>(600, 50, 300, 200, "graphics/WindowBase_01.png");
	plyer_status_window = std::make_shared<Menu>(50, 50, 300, 350, "graphics/WindowBase_01.png");

	//�v���C���[�̍ő�HP���擾����
	max_hp = plyer->PlyerMaxHp(plyer->GetPlayerId());

}


//�X�V����
void Inventory::Update(float delta_time)
{
	//�ŏ��̃��j���[�ł̏���
	if (select_menu == MenuWindow_I::First_Menu) {

		//1�ڂ��I�����ꂽ�ꍇ�A�A�C�e����\������
		if (first_menu->Select_Num == 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			select_menu = MenuWindow_I::ItemMenu;			
			CursorReset();
			currentPage = 0;
		}
		//2�ڂ��I�����ꂽ�ꍇ�A�v���C���[�̋�����\������
		else if (first_menu->Select_Num == 1 && tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			select_menu = MenuWindow_I::StatusMenu;
			
		}
		//3�ڂ��I�����ꂽ�ꍇ�A���j���[�����
		else if (first_menu->Select_Num == 2 && tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			select_menu = MenuWindow_I::Empty;

		}
	}
//-------------------------------------------------------------------------------------------------------------------------------
	//�A�C�e�����j���[�ł̏���
	else if (select_menu == MenuWindow_I::ItemMenu) {

		//Enter�L�[����������ItemUseMenu�ɕύX����
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			select_menu = MenuWindow_I::ItemUseMenu;
			MenuChanege();
		}

   //---�I�������A�C�e���ɂ�ID�Ƃ��Ď擾����---//
  
	// ��L�[�������ꂽ�Ƃ��̏���
	//��ԏ�ɃJ�[�\���������ꍇ����ȏ�ɂ����Ȃ��悤�ɂ���
	if (currentPage == 0 && selectedIndex == 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		// �������Ȃ�
		return;
	}	
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
    if (selectedIndex % item_per_page == 0) {
        // �J�[�\�����y�[�W���̍ŏ㕔�ɂ���ꍇ�́A���̃y�[�W�̍Ō�̗v�f��I��
        if (currentPage > 0) {
            --currentPage;
            // �C���f�b�N�X���X�V���ăy�[�W�̍Ō�̗v�f��I������
            selectedIndex = (currentPage + 1) * item_per_page - 1;
        }
    }
    else {
        // ����ȊO�̏ꍇ�́A���̗v�f��I��
        --selectedIndex;
    }
}

// ���L�[�������ꂽ�Ƃ��̏���
	if (selectedIndex == InventoryList.size() - 1 && tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN))return;
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
    if ((selectedIndex + 1) % item_per_page == 0) {
        // �J�[�\�����y�[�W���̍ŉ����ɂ���ꍇ�́A����̃y�[�W�̍ŏ��̗v�f��I��
		//���̏��v���C���[�����Ă�C���x���g����20�ōl���Ă����4�y�[�W���܂ŊJ����悤�ɂ���
        if (currentPage < 4) {
            ++currentPage;
            // �C���f�b�N�X���X�V���ăy�[�W�̍ŏ��̗v�f��I������
            selectedIndex = currentPage * item_per_page;
        }
    }
    else {
        // ����ȊO�̏ꍇ�́A����̗v�f��I��
        ++selectedIndex;
    }
   }

		// selectedIndex���L���Ȕ͈͓��ɂ��邩�m�F���āA�I�����ꂽ�A�C�e����ID���擾����
		if (selectedIndex >= 0 && selectedIndex < InventoryList.size()) {
			ItemBase selectedItem = InventoryList[selectedIndex];
			selectedItemId = selectedItem.id;
		}
		
			
		CusorMove();
	}

//-------------------------------------------------------------------------------------------------------------------------------
//�A�C�e���ڍ׃��j���[�ł̏���

	else if (select_menu == MenuWindow_I::ItemUseMenu) {
		if (select_detail_window->Select_Num == 0) {
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				InventoryItemUse(selectedItemId);
			}
		}
		else if (select_detail_window->Select_Num == 1) {
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				ItemDetail();
			}
		}
		else if (select_detail_window->Select_Num == 2) {
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				select_menu = MenuWindow_I::ItemMenu;
				MenuChanege();
			}
		}
	}





	

}

//�`�揈��
void Inventory::draw()
{
	
	//�I������Ă���̂��ŏ��̃��j���[��������
	if (select_menu == MenuWindow_I::First_Menu) {
		First_Menu();
	}
	//�I�����ꂽ�̂��A�C�e�����j���[��������
	else if (select_menu == MenuWindow_I::ItemMenu) {
		ItemMenu();
	}
	//�I�����ꂽ�̂��v���C���[�̋������j���[��������
	else if (select_menu == MenuWindow_I::StatusMenu) {
		PlyStatusMenu();
	}
	//�I�����ꂽ�̂��A�C�e���̏ڍ׃��j���[��������
	else if (select_menu == MenuWindow_I::ItemUseMenu) {
		ItemMenu();
		ItemUseMenu();
		if (item_coment == ItemComent::No) {
			item_coment_window->Menu_draw();
			DrawStringEx(item_coment_window->menu_x + 30, item_coment_window->menu_y + 50, -1, "���̃A�C�e���͎g�p�ł��܂���");
		}
	}
	
}

void Inventory::AddInventory(int id)
{
	if (InventoryList.size() == 20) return;
	ItemBase newItem = item->GetItemById(id);
	InventoryList.emplace_back(newItem);
	itemNum++;
}

void Inventory::EquipWeapon(int weaponIndex)
{
	//�A�C�e����0�̏ꍇ�͂Ȃɂ����Ȃ�
	if (itemNum == 0)return;

	//�I�����ꂽ����̃C���f�b�N�X���Ó����m�F
	if (weaponIndex >= 0 && weaponIndex < itemNum)
	{
		//�I�����ꂽ����𑕔����鏈��
		equippedWeapon.push_back(InventoryList[weaponIndex]);

	}

	for (const auto& weapon : equippedWeapon) {
		if (selectCursor == weapon.id && tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			if (weapon.type == WEAPON) {
				equipItem = true;
				plyerstatus.Attack += weapon.damage;
			}

			else if (weapon.type == ARMOR) {

				plyerstatus.Defance += weapon.defance;
			}
		}
		if (weapon.type == EMPTY)
		{
			return;
		}
	}

}

//�A�C�e���̏ڍׂ��J�������̏���
void Inventory::ItemDetail()
{


}

void Inventory::InventoryItemUse(int itemid)
{
	
	if (itemid == 0 || itemid == 1 || itemid == 2 || itemid == 4 || itemid == 5)item_coment = ItemComent::No;
	if (itemid == 3) {
		// �A�C�e��ID��3�ł��v���C���[��HP��MAX�łȂ��ꍇ�ɏ��������s
		if (plyerstatus.hp < max_hp) {
			// HP��30�񕜂�����
			plyerstatus.hp += 30;
			// HP��MAX_HP�𒴂���ꍇ��MAX_HP�ɃN���b�v����
			if (plyerstatus.hp > max_hp) {
				plyerstatus.hp = max_hp;
			}
		}
	}


}

void Inventory::CusorMove()
{
	//�A�C�e�����Ȃ��ꍇ�A�������Ȃ�
	if (itemNum == 0)return;
	//�J�[�\������ԏ�ɂ���ꍇ�J�[�\��������ɏ�ɉ����Ă��J�[�\���𓮂����Ȃ��悤�ɂ���
	if (selectCursor == 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) { return; }
	//�J�[�\���̓���
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		itemNum = GetItemCount();
		selectCursor = (selectCursor + (itemNum - 1)) % itemNum;

	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		itemNum = GetItemCount();

		// �J�[�\�����Ō�̗v�f�������Ɉړ����悤�Ƃ���ꍇ�́A���������ɏ������I������
		if (selectCursor == itemNum - 1) {
			return;
		}

		selectCursor = (selectCursor + 1) % itemNum;
	}
}

void Inventory::CursorReset()
{
	selectCursor = 0;
}

void Inventory::MenuChanege()
{
	
		switch (select_menu)
		{
		case MenuWindow_I::Empty:
			break;
		case MenuWindow_I::First_Menu:
			first_menu->Open();
			First_Menu();
			break;
		case MenuWindow_I::ItemMenu:
			ItemMenu();
			break;
		case MenuWindow_I::StatusMenu:
			PlyStatusMenu();
			break;
		case MenuWindow_I::ItemUseMenu:
			item_coment = ItemComent::Empty;
			select_detail_window->Open();
			ItemUseMenu();
			break;

		default:
			break;
		}
	

}

void Inventory::First_Menu()
{
	first_menu->All();



}

void Inventory::ItemMenu()
{
	int i = 0;
	menu_window->Menu_draw();

		

		//1�y�[�W������̃A�C�e����
		item_per_page = 5;

		//���݂̃y�[�W�Ɋ�Â��ĕ\������A�C�e���͈̔͂��v�Z
		start_index = currentPage * item_per_page;
		end_index = min((start_index + item_per_page) , InventoryList.size());

		for (int index = start_index; index < end_index; ++index) {
			//
			auto& InventoryData = InventoryList[index];
			//�A�C�e���̖��O���擾����
			std::string ItemName = InventoryData.name;

			// �A�C�e���̕`��
			DrawStringEx(menu_window->menu_x + 60, menu_window->menu_y + 50 + 34 * i, -1, "%s", ItemName.c_str());

			// �J�[�\����`�悷��ʒu������
			int cursorY = menu_window->menu_y + 50 + 34 * (selectCursor % item_per_page);
			DrawRotaGraph(menu_window->menu_x + 20, cursorY, 0.3f, 0, cursorGh, true);
		
			//�����ł���A�C�e���������ꍇ
			if (InventoryData.type == 1 || InventoryData.type == 2) {
				//�������̃A�C�e���������ꍇ�AE������
				if (equipItem)DrawStringEx(menu_window->menu_x + 30, menu_window->menu_y + 50 + 30 * i, -1, "[E]");
				++i;
			}
			//�g�p�A�C�e���������ꍇ
			else
			{
				++i;
			}
			
		}
		//�y�[�W�̕\��
		DrawStringEx(menu_window->menu_x + 50, menu_window->menu_y + 230,-1, "%d / 4", currentPage + 1);

		DrawStringEx(500, 450, -1, "���݂̃y�[�W : %d", currentPage);
		DrawStringEx(500, 500, -1, "�A�C�e����ID : %d", selectedItemId);
		DrawStringEx(500, 550, -1, "�J�[�\���ʒu : %d", selectCursor);


}

void Inventory::PlyStatusMenu()
{
	plyer_status_window->Menu_draw();
	Player::PlyerStatus plyStatus = plyer->GetPlyerStatus(plyer->GetPlayerId());
	std::list<Player::PlyerStatus>plyerStatusList;
	plyerStatusList.emplace_back(plyStatus);

	DrawStringEx(150, 70, -1, "===����===");

	for (const auto& PlayerStatus : plyerStatusList) {

		DrawStringEx(70, 100, -1, "HP : %d", PlayerStatus.hp);
		DrawStringEx(70, 150, -1, "�U���� : %d", PlayerStatus.Attack);
		DrawStringEx(70, 200, -1, "�h��� : %d", PlayerStatus.Defance);
		DrawStringEx(70, 250, -1, "���x�� : %d", PlayerStatus.level);
		DrawStringEx(70, 300, -1, "���΂₳ : %d", PlayerStatus.Speed);
		DrawStringEx(70, 350, -1, "���x���A�b�v�ɕK�v�Ȍo���l : %d", PlayerStatus.R_expoint);
	}


}


void Inventory::ItemUseMenu()
{
	
	select_detail_window->All();




}
