#pragma once
///
///アイテムを管理するクラス
/// 
#include<string>
#include "../dxlib_ext/dxlib_ext.h"
#include"../Manager/GameManager.h"
#include"../Item/ItemBase.h"



class Item : public  ItemBase{
public:
	
	Item();
	~Item();

	void update(float delta_time);
	void draw();

	


private:

//------------------------------------------------------------------------------------------------------------------------
//ポインタ

	Shared<GameManager>gManager = nullptr;



	//読み込み関数
	void ItemLoadTypeInfo();
	
	//modelを入れる変数
	ItemBase item_Status_ary;

	//構造体の総数
	int m_item_Status_Total_num;

	//Csv読み取り用の配列
	std::vector<std::vector<tnl::CsvCell>>m_itemStatus_Csv_Info;

	//構造体を格納する配列
	std::list<ItemBase>m_Item_Status_Type;

	//アイテムなどの説明文などを入れる配列
	std::string ItemDisc = {};

	//itemの座標
	tnl::Vector3 item_pos = {};

public:

	/*ItemStatus GetModelTypeInfo(int id);*/

	//IDを指定してアイテムを取得する関数
	ItemBase GetItemById(int id) const {
		auto it = std::find_if(m_Item_Status_Type.begin(), m_Item_Status_Type.end(),
			[id](const ItemBase& item) { return item.id == id; });

		if (it != m_Item_Status_Type.end()) {
			return *it;
		}
		else {
			// IDに対応するアイテムが見つからない場合は、適当なデフォルト値を返すかエラー処理を行うなど
			return ItemBase{};
		}
	}

	//それぞれのアイテムで武器の説明を入れる
	void SetItemDisc(std::string itemDisc_) { ItemDisc = itemDisc_; }
	


};