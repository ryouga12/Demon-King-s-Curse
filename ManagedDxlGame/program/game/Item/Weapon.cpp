#include "Weapon.h"
#include<iostream>
#include<algorithm>

Weapon::Weapon() 
{
	item_ = std::make_shared<Item>();

	WeaponInint();

	
}

void Weapon::draw()
{
	/*DrawStringEx()*/


}

void Weapon::WeaponInint()
{
	//一個目の店
	weponList.emplace_back(item_->GetItemById(0));
	weponList.emplace_back(item_->GetItemById(4));
	weponList.emplace_back(item_->GetItemById(5));
	weponList.emplace_back(item_->GetItemById(1));
	weponList.emplace_back(item_->GetItemById(2));
	weponList.emplace_back(item_->GetItemById(3));


	//値段が低い順にソート
	std::sort(weponList.begin(), weponList.end(), [](const ItemBase& left, const ItemBase& right) {
		return left.price < right.price;
		});

	weapon_disc[0] = { "木で作られている剣 : 特に効果はない" };
	weapon_disc[1] = { "木で作られているハンマー : 特に効果はない" };
	weapon_disc[2] = { "銅で作られている剣 : 特に効果はない" };
	weapon_disc[3] = { "革で作られた鎧 : 特に効果はない"};
	weapon_disc[4] = { "革で作られた盾 : 特に効果はない"};
	weapon_disc[5] = { "一般的な薬草 　: 使うとHPが少し回復する" };


}


