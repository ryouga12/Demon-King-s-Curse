#pragma once
#include"../Item/Item.h"
#include"../Object/Player.h"
#include"../Manager/GameManager.h"
#include"../Menu/MenuWindow.h"



class Inventory
{
public:

	Inventory();

	void Update(float delta_time);
	void draw();

	//内部にItemを20個持つlist
	std::vector<ItemBase>InventoryList;

	//内部にItemを50持つlist
	/*std::vector<ItemBase>InventoryBagList;*/

	//アイテムを追加する関数
	void AddInventory(int id);

	//アイテムの袋に追加する関数
	/*void AddBagInventory(int id);*/

	//アイテムを装備する関数
	void EquipWeapon(int weaponIndex);

	//アイテムの詳細などの処理
	void ItemDetail();

	//アイテムをの番号によって処理をする
	void InventoryItemUse(int itemid);


	//インベントリ内のアイテムの数を取得する関数
	inline int GetItemCount() {
		return InventoryList.size();
	}
	
	//インベントリのリストを他のクラスで使う
	std::vector<ItemBase>& GetInventoryList() {
		return InventoryList;
	}

	//インベントリの切り替えの為のクラス
	enum class MenuWindow_I {
		Empty,
		First_Menu,
		ItemMenu,
		StatusMenu,
		ItemUseMenu
	};

	MenuWindow_I select_menu = MenuWindow_I::Empty;

	int max_hp = 0;
	

//------------------------------------------------------------------------------------------------------------------------
//---関数---//

	//カーソルを上下に動かす関数
	void CusorMove();
	//カーソルを一番上に戻す関数
	void CursorReset();
	//インベントリを切り替える
	void MenuChanege();
	

//------------------------------------------------------------------------------------------------------------------------
//---メニュー---//

	//最初のメニュー
	void First_Menu();
	//アイテムのメニュー
	void ItemMenu();
	//プレイヤーのステータスを表示するメニュー
	void PlyStatusMenu();
	//武器の中の詳細や使うための描画
	void ItemUseMenu();
	//今どのページにいるか
	int currentPage = 0;
	//1ページあたりのアイテム数
	int item_per_page = 5;
	//ユーザーが選択した要素のインデックス
	//最初は一番上なので0に設定する
	int selectedIndex = 0;
	//取得したアイテムのIDを一時的に保持するための変数
	int selectedItemId = 0;

//アイテムの描画で使うインデックス
//  
	//最初の番号
	int start_index = 0;
	//最後の番号
	int end_index = 0;
	

private:

	enum  {
		EMPTY,
		WEAPON,
		ARMOR
	};

	//インベントリ内のアイテム数
	int itemNum = 0;

	//選択中のカーソルの位置
	int selectCursor = 0;

	//武器を装備する
	std::vector<ItemBase> equippedWeapon;

	//playerのステータス
	Player::PlyerStatus plyerstatus;

	//plyerStatusのid番号
	int PlyerStatus_Id;

	//武器の装備が可能か
	bool equipItem = false;
	
	//カーソルのghdl
	int cursorGh = 0;

	//プレイヤーのステータスを取得する為のID
	int PlyerId = 1;

	//ItemのComentを切り替える為のクラス
	enum class ItemComent {
		Empty,
		No,
		Use,
	};

	ItemComent item_coment = ItemComent::Empty;


//------------------------------------------------------------------------------------------------------------------------
//ポインタ
	Shared<Item>item = nullptr;
	Shared<Player>plyer = nullptr;
	Shared<GameManager>gm_Manager = nullptr;
	Shared<MenuWindow>first_menu = nullptr;
	Shared<MenuWindow>select_action_menu = nullptr;
	Shared<MenuWindow>select_detail_window = nullptr;
	Shared<Menu>menu_window = nullptr;
	Shared<Menu>item_coment_window = nullptr;
	Shared<Menu>plyer_status_window = nullptr;

	
};