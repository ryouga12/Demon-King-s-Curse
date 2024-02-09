#include "Item.h"
#include <vector>
#include <algorithm>


Item::Item()
{

	gManager = std::make_shared<GameManager>();
	

	if (m_itemStatus_Csv_Info.size() == 0) {
		m_itemStatus_Csv_Info = tnl::LoadCsv<tnl::CsvCell>("csv/Item.csv");
		ItemLoadTypeInfo();
	}

	
}

Item::~Item()
{

}

void Item::update(float delta_time)
{

}



void Item::ItemLoadTypeInfo()
{
	int max_num = m_itemStatus_Csv_Info.size();

	m_item_Status_Total_num = max_num;

	for (int y = 1; y < max_num; y++) {
		ItemBase itemStatus_info;

		//csvからnameの取得
		itemStatus_info.name = m_itemStatus_Csv_Info[y][0].getString();
		//csvからidの取得
		itemStatus_info.id = m_itemStatus_Csv_Info[y][1].getInt();
		//csvからtypeの取得
		itemStatus_info.type = m_itemStatus_Csv_Info[y][2].getInt();
		//csvからDamageの取得
		itemStatus_info.damage = m_itemStatus_Csv_Info[y][3].getInt();
		//csvからEpicの取得
		itemStatus_info.epic = m_itemStatus_Csv_Info[y][4].getInt();
		//csvからdefanceの取得
		itemStatus_info.defance = m_itemStatus_Csv_Info[y][5].getInt();
		//csvからpriceを取得
		itemStatus_info.price = m_itemStatus_Csv_Info[y][6].getInt();

		m_Item_Status_Type.emplace_back(itemStatus_info);
	}

	//std::sort(m_Item_Status_Type.begin(), m_Item_Status_Type.end(), ItemStatus{}.id);

	//ダメージ順にソート
	m_Item_Status_Type.sort([](const Item::ItemBase& left, const Item::ItemBase& right){
		return left.damage > right.damage;
	});

}

void Item::draw()
{
	
}


//Item::ItemStatus Item::GetModelTypeInfo(int id)
//{
//	for (const auto& model : m_Item_Status_Type) {
//
//		if (model.id == id)
//		{
//			return model;
//		}
//	}
//
//	//IDが見つからなかった場合はデフォルト値
//	return ItemStatus();
//}
