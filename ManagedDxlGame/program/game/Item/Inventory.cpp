#include "Inventory.h"



Inventory::Inventory()
{
	item = std::make_shared<Item>();
	plyer = std::make_shared<Player>();
	gm_Manager = std::make_shared<GameManager>();


	plyerstatus = plyer->GetPlyerStatus(PlyerStatus_Id);

	cursorGh = gm_Manager->LoadGraphEX("graphics/cur_sannkaku2.png");

	//最初のESCを押したときに出る最初のメニュー
	MenuWindow::MenuElement_t* first_menu_coment = new MenuWindow::MenuElement_t[]
	{
		{100, 100 , "道具",0},
		{100, 150 , "強さ",1},
		{100, 200 , "閉じる",2}
	};

	first_menu = std::make_shared<MenuWindow>(50, 50, 250, 200, "graphics/WindowBase_01.png", first_menu_coment, 3, 1);

	//プレイヤーの選択してもらうメニュー
	MenuWindow::MenuElement_t* select_menu_coment = new MenuWindow::MenuElement_t[]
	{
		{ 100 , 100 , "はい" , 0},
		{ 100 , 150 , "いいえ" , 1}
	};

	select_action_menu = std::make_shared<MenuWindow>(50, 50, 250, 200, "graphics/WindowBase_01.png", select_menu_coment, 2, 1);

	//アイテムウィンドウ内で選択するメニュー
	MenuWindow::MenuElement_t* select_detail = new MenuWindow::MenuElement_t[]
	{
		{400 , 100 , "使う" , 0},
		{400 , 150 , "詳細" , 1},
		{400 , 200 , "閉じる" , 2}
	};

	select_detail_window = std::make_shared<MenuWindow>(350, 50, 250, 200, "graphics/WindowBase_01.png", select_detail, 3, 1);

	//メニューウィンドウ
	menu_window = std::make_shared<Menu>(50, 50, 300, 270, "graphics/WindowBase_01.png");
	item_coment_window = std::make_shared<Menu>(600, 50, 300, 200, "graphics/WindowBase_01.png");
	plyer_status_window = std::make_shared<Menu>(50, 50, 300, 350, "graphics/WindowBase_01.png");

	//プレイヤーの最大HPを取得する
	max_hp = plyer->PlyerMaxHp(plyer->GetPlayerId());

}


//更新処理
void Inventory::Update(float delta_time)
{
	//最初のメニューでの処理
	if (select_menu == MenuWindow_I::First_Menu) {

		//1個目が選択された場合、アイテムを表示する
		if (first_menu->Select_Num == 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			select_menu = MenuWindow_I::ItemMenu;			
			CursorReset();
			currentPage = 0;
		}
		//2個目が選択された場合、プレイヤーの強さを表示する
		else if (first_menu->Select_Num == 1 && tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			select_menu = MenuWindow_I::StatusMenu;
			
		}
		//3個目が選択された場合、メニューを閉じる
		else if (first_menu->Select_Num == 2 && tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			select_menu = MenuWindow_I::Empty;

		}
	}
//-------------------------------------------------------------------------------------------------------------------------------
	//アイテムメニューでの処理
	else if (select_menu == MenuWindow_I::ItemMenu) {

		//Enterキーを押したらItemUseMenuに変更する
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			select_menu = MenuWindow_I::ItemUseMenu;
			MenuChanege();
		}

   //---選択したアイテムにをIDとして取得する---//
  
	// 上キーが押されたときの処理
	//一番上にカーソルがいた場合それ以上にいかないようにする
	if (currentPage == 0 && selectedIndex == 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		// 何もしない
		return;
	}	
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
    if (selectedIndex % item_per_page == 0) {
        // カーソルがページ内の最上部にいる場合は、一つ上のページの最後の要素を選択
        if (currentPage > 0) {
            --currentPage;
            // インデックスを更新してページの最後の要素を選択する
            selectedIndex = (currentPage + 1) * item_per_page - 1;
        }
    }
    else {
        // それ以外の場合は、一つ上の要素を選択
        --selectedIndex;
    }
}

// 下キーが押されたときの処理
	if (selectedIndex == InventoryList.size() - 1 && tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN))return;
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
    if ((selectedIndex + 1) % item_per_page == 0) {
        // カーソルがページ内の最下部にいる場合は、一つ下のページの最初の要素を選択
		//今の所プレイヤーが持てるインベントリは20で考えている為4ページ分まで開けるようにする
        if (currentPage < 4) {
            ++currentPage;
            // インデックスを更新してページの最初の要素を選択する
            selectedIndex = currentPage * item_per_page;
        }
    }
    else {
        // それ以外の場合は、一つ下の要素を選択
        ++selectedIndex;
    }
   }

		// selectedIndexが有効な範囲内にあるか確認して、選択されたアイテムのIDを取得する
		if (selectedIndex >= 0 && selectedIndex < InventoryList.size()) {
			ItemBase selectedItem = InventoryList[selectedIndex];
			selectedItemId = selectedItem.id;
		}
		
			
		CusorMove();
	}

//-------------------------------------------------------------------------------------------------------------------------------
//アイテム詳細メニューでの処理

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

//描画処理
void Inventory::draw()
{
	
	//選択されているのが最初のメニューだったら
	if (select_menu == MenuWindow_I::First_Menu) {
		First_Menu();
	}
	//選択されたのがアイテムメニューだったら
	else if (select_menu == MenuWindow_I::ItemMenu) {
		ItemMenu();
	}
	//選択されたのがプレイヤーの強さメニューだったら
	else if (select_menu == MenuWindow_I::StatusMenu) {
		PlyStatusMenu();
	}
	//選択されたのがアイテムの詳細メニューだったら
	else if (select_menu == MenuWindow_I::ItemUseMenu) {
		ItemMenu();
		ItemUseMenu();
		if (item_coment == ItemComent::No) {
			item_coment_window->Menu_draw();
			DrawStringEx(item_coment_window->menu_x + 30, item_coment_window->menu_y + 50, -1, "このアイテムは使用できません");
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
	//アイテムが0の場合はなにもしない
	if (itemNum == 0)return;

	//選択された武器のインデックスが妥当か確認
	if (weaponIndex >= 0 && weaponIndex < itemNum)
	{
		//選択された武器を装備する処理
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

//アイテムの詳細を開いた時の処理
void Inventory::ItemDetail()
{


}

void Inventory::InventoryItemUse(int itemid)
{
	
	if (itemid == 0 || itemid == 1 || itemid == 2 || itemid == 4 || itemid == 5)item_coment = ItemComent::No;
	if (itemid == 3) {
		// アイテムIDが3でかつプレイヤーのHPがMAXでない場合に処理を実行
		if (plyerstatus.hp < max_hp) {
			// HPを30回復させる
			plyerstatus.hp += 30;
			// HPがMAX_HPを超える場合はMAX_HPにクリップする
			if (plyerstatus.hp > max_hp) {
				plyerstatus.hp = max_hp;
			}
		}
	}


}

void Inventory::CusorMove()
{
	//アイテムがない場合、何もしない
	if (itemNum == 0)return;
	//カーソルが一番上にいる場合カーソルをさらに上に押してもカーソルを動かさないようにする
	if (selectCursor == 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) { return; }
	//カーソルの動き
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		itemNum = GetItemCount();
		selectCursor = (selectCursor + (itemNum - 1)) % itemNum;

	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		itemNum = GetItemCount();

		// カーソルが最後の要素よりも下に移動しようとする場合は、何もせずに処理を終了する
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

		

		//1ページ当たりのアイテム数
		item_per_page = 5;

		//現在のページに基づいて表示するアイテムの範囲を計算
		start_index = currentPage * item_per_page;
		end_index = min((start_index + item_per_page) , InventoryList.size());

		for (int index = start_index; index < end_index; ++index) {
			//
			auto& InventoryData = InventoryList[index];
			//アイテムの名前を取得する
			std::string ItemName = InventoryData.name;

			// アイテムの描画
			DrawStringEx(menu_window->menu_x + 60, menu_window->menu_y + 50 + 34 * i, -1, "%s", ItemName.c_str());

			// カーソルを描画する位置を決定
			int cursorY = menu_window->menu_y + 50 + 34 * (selectCursor % item_per_page);
			DrawRotaGraph(menu_window->menu_x + 20, cursorY, 0.3f, 0, cursorGh, true);
		
			//装備できるアイテムだった場合
			if (InventoryData.type == 1 || InventoryData.type == 2) {
				//装備中のアイテムだった場合、Eをつける
				if (equipItem)DrawStringEx(menu_window->menu_x + 30, menu_window->menu_y + 50 + 30 * i, -1, "[E]");
				++i;
			}
			//使用アイテムだった場合
			else
			{
				++i;
			}
			
		}
		//ページの表示
		DrawStringEx(menu_window->menu_x + 50, menu_window->menu_y + 230,-1, "%d / 4", currentPage + 1);

		DrawStringEx(500, 450, -1, "現在のページ : %d", currentPage);
		DrawStringEx(500, 500, -1, "アイテムのID : %d", selectedItemId);
		DrawStringEx(500, 550, -1, "カーソル位置 : %d", selectCursor);


}

void Inventory::PlyStatusMenu()
{
	plyer_status_window->Menu_draw();
	Player::PlyerStatus plyStatus = plyer->GetPlyerStatus(plyer->GetPlayerId());
	std::list<Player::PlyerStatus>plyerStatusList;
	plyerStatusList.emplace_back(plyStatus);

	DrawStringEx(150, 70, -1, "===強さ===");

	for (const auto& PlayerStatus : plyerStatusList) {

		DrawStringEx(70, 100, -1, "HP : %d", PlayerStatus.hp);
		DrawStringEx(70, 150, -1, "攻撃力 : %d", PlayerStatus.Attack);
		DrawStringEx(70, 200, -1, "防御力 : %d", PlayerStatus.Defance);
		DrawStringEx(70, 250, -1, "レベル : %d", PlayerStatus.level);
		DrawStringEx(70, 300, -1, "すばやさ : %d", PlayerStatus.Speed);
		DrawStringEx(70, 350, -1, "レベルアップに必要な経験値 : %d", PlayerStatus.R_expoint);
	}


}


void Inventory::ItemUseMenu()
{
	
	select_detail_window->All();




}
