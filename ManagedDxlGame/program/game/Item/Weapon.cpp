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
	//��ڂ̓X
	weponList.emplace_back(item_->GetItemById(0));
	weponList.emplace_back(item_->GetItemById(4));
	weponList.emplace_back(item_->GetItemById(5));
	weponList.emplace_back(item_->GetItemById(1));
	weponList.emplace_back(item_->GetItemById(2));
	weponList.emplace_back(item_->GetItemById(3));


	//�l�i���Ⴂ���Ƀ\�[�g
	std::sort(weponList.begin(), weponList.end(), [](const ItemBase& left, const ItemBase& right) {
		return left.price < right.price;
		});

	weapon_disc[0] = { "�؂ō���Ă��錕 : ���Ɍ��ʂ͂Ȃ�" };
	weapon_disc[1] = { "�؂ō���Ă���n���}�[ : ���Ɍ��ʂ͂Ȃ�" };
	weapon_disc[2] = { "���ō���Ă��錕 : ���Ɍ��ʂ͂Ȃ�" };
	weapon_disc[3] = { "�v�ō��ꂽ�Z : ���Ɍ��ʂ͂Ȃ�"};
	weapon_disc[4] = { "�v�ō��ꂽ�� : ���Ɍ��ʂ͂Ȃ�"};
	weapon_disc[5] = { "��ʓI�Ȗ� �@: �g����HP�������񕜂���" };


}


