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

	//������Item��20����list
	std::vector<ItemBase>InventoryList;

	//������Item��50����list
	/*std::vector<ItemBase>InventoryBagList;*/

	//�A�C�e����ǉ�����֐�
	void AddInventory(int id);

	//�A�C�e���̑܂ɒǉ�����֐�
	/*void AddBagInventory(int id);*/

	//�A�C�e���𑕔�����֐�
	void EquipWeapon(int weaponIndex);

	//�A�C�e���̏ڍׂȂǂ̏���
	void ItemDetail();

	//�A�C�e�����̔ԍ��ɂ���ď���������
	void InventoryItemUse(int itemid);


	//�C���x���g�����̃A�C�e���̐����擾����֐�
	inline int GetItemCount() {
		return InventoryList.size();
	}
	
	//�C���x���g���̃��X�g�𑼂̃N���X�Ŏg��
	std::vector<ItemBase>& GetInventoryList() {
		return InventoryList;
	}

	//�C���x���g���̐؂�ւ��ׂ̈̃N���X
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
//---�֐�---//

	//�J�[�\�����㉺�ɓ������֐�
	void CusorMove();
	//�J�[�\������ԏ�ɖ߂��֐�
	void CursorReset();
	//�C���x���g����؂�ւ���
	void MenuChanege();
	

//------------------------------------------------------------------------------------------------------------------------
//---���j���[---//

	//�ŏ��̃��j���[
	void First_Menu();
	//�A�C�e���̃��j���[
	void ItemMenu();
	//�v���C���[�̃X�e�[�^�X��\�����郁�j���[
	void PlyStatusMenu();
	//����̒��̏ڍׂ�g�����߂̕`��
	void ItemUseMenu();
	//���ǂ̃y�[�W�ɂ��邩
	int currentPage = 0;
	//1�y�[�W������̃A�C�e����
	int item_per_page = 5;
	//���[�U�[���I�������v�f�̃C���f�b�N�X
	//�ŏ��͈�ԏ�Ȃ̂�0�ɐݒ肷��
	int selectedIndex = 0;
	//�擾�����A�C�e����ID���ꎞ�I�ɕێ����邽�߂̕ϐ�
	int selectedItemId = 0;

//�A�C�e���̕`��Ŏg���C���f�b�N�X
//  
	//�ŏ��̔ԍ�
	int start_index = 0;
	//�Ō�̔ԍ�
	int end_index = 0;
	

private:

	enum  {
		EMPTY,
		WEAPON,
		ARMOR
	};

	//�C���x���g�����̃A�C�e����
	int itemNum = 0;

	//�I�𒆂̃J�[�\���̈ʒu
	int selectCursor = 0;

	//����𑕔�����
	std::vector<ItemBase> equippedWeapon;

	//player�̃X�e�[�^�X
	Player::PlyerStatus plyerstatus;

	//plyerStatus��id�ԍ�
	int PlyerStatus_Id;

	//����̑������\��
	bool equipItem = false;
	
	//�J�[�\����ghdl
	int cursorGh = 0;

	//�v���C���[�̃X�e�[�^�X���擾����ׂ�ID
	int PlyerId = 1;

	//Item��Coment��؂�ւ���ׂ̃N���X
	enum class ItemComent {
		Empty,
		No,
		Use,
	};

	ItemComent item_coment = ItemComent::Empty;


//------------------------------------------------------------------------------------------------------------------------
//�|�C���^
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