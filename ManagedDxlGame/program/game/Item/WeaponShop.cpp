#include "WeaponShop.h"

WeaponShop::WeaponShop()
{
	weapon_ = std::make_shared<Weapon>();
	// inventory = std::make_shared<Inventory>();
	myplayer = std::make_shared<Player>();
	gm_manager = std::make_shared<GameManager>();
	cousor_hdl = gm_manager->LoadGraphEX("graphics/cur_sannkaku2.png");
	menuWindow = std::make_shared<Menu>(50, 50, 350, 400, "graphics/WindowBase_01.png");

}

void WeaponShop::Update(float delta_time)
{
	WeaponShopCursorMove();
}

void WeaponShop::Draw()
{
	//���j���[�̕\��
	menuWindow->Menu_draw();

	//���퉮�֘A�̕\��
	DrawString(60, 520, "���퉮", -1);

	DrawString(110, 70, "===== ���퉮 =====", -1);

	for (int i = 0; i < weapon_->weponList.size(); ++i) {
		DrawStringEx(85, 130 + i * 40, -1, "%d. %s \n(�З�: %d, �h���: %d,���i: %d)", i + 1, weapon_->weponList[i].name.c_str(), weapon_->weponList[i].damage,weapon_->weponList[i].defance, weapon_->weponList[i].price);
	}
	DrawString(85, 380, "�w������������̔ԍ���\n�I�����Ă�������(0: �I��)", -1);


	if (buyWeapon == B_Weapon::buy) {
		DrawString(150, 620, "�u���x����!���肪�ƂˁI�v", -1);
	}
	else if (buyWeapon == B_Weapon::no) {
		DrawString(150, 620, "�u����������Ȃ���!�o�����Ă���!�v", -1);
	}

	DrawRotaGraph(70, 140 +  SelectCousor * 40 , 0.3f, 0, cousor_hdl, true);
	DrawStringEx(100, 700, -1, "%d", weapon_->GetWeaponListCount());


}

//�J�[�\���̓���
void WeaponShop::WeaponShopCursorMove()
{
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		WeaponNum = weapon_->GetWeaponListCount();
		SelectCousor = (SelectCousor + (WeaponNum - 1)) % WeaponNum;
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		WeaponNum = weapon_->GetWeaponListCount();
		SelectCousor = (SelectCousor + 1) % WeaponNum;
	}

	

}

void WeaponShop::BuyWeapon(std::shared_ptr<Player>& player)
{
	if (SelectCousor == 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		if (inventory->GetInventoryList().size() == 20) return;
		if (player->money >= weapon_->weponList[0].price) {
			player->money -= weapon_->weponList[0].price;
			inventory->AddInventory(weapon_->weponList[0].id);
			buyWeapon = B_Weapon::buy;
		}
		else
		{
			buyWeapon = B_Weapon::no;
		}

	}
	if (SelectCousor == 1 && tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		if (inventory->GetInventoryList().size() == 20) return;
		if (player->money >= weapon_->weponList[1].price) {
			player->money -= weapon_->weponList[1].price;
			inventory->AddInventory(weapon_->weponList[1].id);
			buyWeapon = B_Weapon::buy;
		}
		else {
			buyWeapon = B_Weapon::no;
		}

	}
	if (SelectCousor == 2 && tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		if (inventory->GetInventoryList().size() == 20) return;
		if (player->money >= weapon_->weponList[2].price) {
			player->money -= weapon_->weponList[2].price;
			inventory->AddInventory(weapon_->weponList[2].id);
			buyWeapon = B_Weapon::buy;
		}
		else {
			buyWeapon = B_Weapon::no;
		}
	}
	if (SelectCousor == 3 && tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		if (inventory->GetInventoryList().size() == 20) return;
		if (player->money >= weapon_->weponList[3].price) {
			player->money -= weapon_->weponList[3].price;
			inventory->AddInventory(weapon_->weponList[3].id);
			buyWeapon = B_Weapon::buy;
		}
		else {
			buyWeapon = B_Weapon::no;
		}
	}
	if (SelectCousor == 4 && tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		if (inventory->GetInventoryList().size() == 20) return;
		if (player->money >= weapon_->weponList[4].price) {
			player->money -= weapon_->weponList[4].price;
			inventory->AddInventory(weapon_->weponList[4].id);
			buyWeapon = B_Weapon::buy;
		}
		else {
			buyWeapon = B_Weapon::no;
		}
	}
	if (SelectCousor == 5 && tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		if (inventory->GetInventoryList().size() == 20) return;
		if (player->money >= weapon_->weponList[5].price) {
			player->money -= weapon_->weponList[5].price;
			inventory->AddInventory(weapon_->weponList[5].id);
			buyWeapon = B_Weapon::buy;
		}
		else {
			buyWeapon = B_Weapon::no;
		}
	}

}
