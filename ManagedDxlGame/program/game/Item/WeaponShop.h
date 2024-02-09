#pragma once
#include"../Object/Player.h"
#include"Weapon.h"
#include"Inventory.h"
#include"../Menu/MenuWindow.h"
#include"../Manager/GameManager.h"


class WeaponShop {
public:

	WeaponShop();

	void Update(float delta_time);

	void Draw();

	void BuyWeapon(Shared<Player>& player);

	void WeaponShopCursorMove();

	void setInventory(std::shared_ptr<Inventory> i) { inventory = i; }


	
//------------------------------------------------------------------------------------------------------------------------
//�|�C���^

	Shared<Weapon>weapon_ = nullptr;
	Shared<Inventory>inventory = nullptr;
	Shared<Player>myplayer = nullptr;
	Shared<MenuWindow>use_equip = nullptr;
	Shared<GameManager>gm_manager = nullptr;
	Shared<Menu>menuWindow = nullptr;

private:

//------------------------------------------------------------------------------------------------------------------------
//����֌W

	//���킪��������
	enum class B_Weapon {
		empty,
		buy,
		no,
	};

	//����̑���
	int WeaponNum = 0;

	//�J�[�\���̓���
	int SelectCousor = 0;

	//�J�[�\���̃n���h��
	int cousor_hdl;

	//�J�[�\���̍��W
	int coursorY = 0;

public:

	B_Weapon buyWeapon = B_Weapon::empty;

	B_Weapon buyComentClear() {
		return B_Weapon::empty;
	}


};