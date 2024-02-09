#pragma once
///
///�A�C�e�����Ǘ�����N���X
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
//�|�C���^

	Shared<GameManager>gManager = nullptr;



	//�ǂݍ��݊֐�
	void ItemLoadTypeInfo();
	
	//model������ϐ�
	ItemBase item_Status_ary;

	//�\���̂̑���
	int m_item_Status_Total_num;

	//Csv�ǂݎ��p�̔z��
	std::vector<std::vector<tnl::CsvCell>>m_itemStatus_Csv_Info;

	//�\���̂��i�[����z��
	std::list<ItemBase>m_Item_Status_Type;

	//�A�C�e���Ȃǂ̐������Ȃǂ�����z��
	std::string ItemDisc = {};

	//item�̍��W
	tnl::Vector3 item_pos = {};

public:

	/*ItemStatus GetModelTypeInfo(int id);*/

	//ID���w�肵�ăA�C�e�����擾����֐�
	ItemBase GetItemById(int id) const {
		auto it = std::find_if(m_Item_Status_Type.begin(), m_Item_Status_Type.end(),
			[id](const ItemBase& item) { return item.id == id; });

		if (it != m_Item_Status_Type.end()) {
			return *it;
		}
		else {
			// ID�ɑΉ�����A�C�e����������Ȃ��ꍇ�́A�K���ȃf�t�H���g�l��Ԃ����G���[�������s���Ȃ�
			return ItemBase{};
		}
	}

	//���ꂼ��̃A�C�e���ŕ���̐���������
	void SetItemDisc(std::string itemDisc_) { ItemDisc = itemDisc_; }
	


};